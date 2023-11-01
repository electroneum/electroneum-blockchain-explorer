# Use ubuntu:20.04 as base for builder stage image
FROM ubuntu:20.04 as builder

# Set Electroneum branch/tag to be used for electroneumd compilation

ARG ELECTRONEUM_BRANCH=master

# Added DEBIAN_FRONTEND=noninteractive to workaround tzdata prompt on installation
ENV DEBIAN_FRONTEND="noninteractive"

# Install dependencies for electroneumd and etnblocks compilation
RUN apt-get update \
  && apt-get upgrade -y \
  && apt-get install -y --no-install-recommends \
  git \
  build-essential \
  cmake \
  miniupnpc \
  graphviz \
  doxygen \
  pkg-config \
  ca-certificates \
  zip \
  libboost-all-dev \
  libunbound-dev \
  libunwind8-dev \
  libssl-dev \
  libcurl4-openssl-dev \
  libgtest-dev \
  libreadline-dev \
  libzmq3-dev \
  libsodium-dev \
  libhidapi-dev \
  libhidapi-libusb0 \
  liblzma-dev \
  libldns-dev \
  libexpat1-dev \
  libpgm-dev \
  libusb-dev \
  libsecp256k1-dev \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Set compilation environment variables
ENV CFLAGS='-fPIC'
ENV CXXFLAGS='-fPIC'
ENV USE_SINGLE_BUILDDIR 1
ENV BOOST_DEBUG         1

WORKDIR /root

# Clone and compile electroneumd with all available threads
ARG NPROC
RUN git clone --recursive --branch ${ELECTRONEUM_BRANCH} https://github.com/electroneum/electroneum.git \
  && cd electroneum \
  && test -z "$NPROC" && nproc > /nproc || echo -n "$NPROC" > /nproc && make -j"$(cat /nproc)"


# Copy and cmake/make etnblocks with all available threads
COPY . /root/electroneum-blockchain-explorer/
WORKDIR /root/electroneum-blockchain-explorer/build
RUN cmake .. && make -j"$(cat /nproc)"

# Use ldd and awk to bundle up dynamic libraries for the final image
RUN zip /lib.zip $(ldd etnblocks | grep -E '/[^\ ]*' -o)

# Use ubuntu:20.04 as base for final image
FROM ubuntu:20.04

# Added DEBIAN_FRONTEND=noninteractive to workaround tzdata prompt on installation
ENV DEBIAN_FRONTEND="noninteractive"

# Install unzip to handle bundled libs from builder stage
RUN apt-get update \
  && apt-get upgrade -y \
  && apt-get install -y --no-install-recommends unzip \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

COPY --from=builder /lib.zip .
RUN unzip -o lib.zip && rm -rf lib.zip

# Add user and setup directories for electroneumd and etnblocks
RUN useradd -ms /bin/bash electroneum \
  && mkdir -p /home/electroneum/.electroneum \
  && chown -R electroneum:electroneum /home/electroneum/.electroneum
USER electroneum

# Switch to home directory and install newly built etnblocks binary
WORKDIR /home/electroneum
COPY --chown=electroneum:electroneum --from=builder /root/electroneum-blockchain-explorer/build/etnblocks .
COPY --chown=electroneum:electroneum --from=builder /root/electroneum-blockchain-explorer/build/templates ./templates/

# Expose volume used for lmdb access by etnblocks
VOLUME /home/electroneum/.electroneum

# Expose default explorer http port
EXPOSE 8081

ENTRYPOINT ["/bin/sh", "-c"]

# Set sane defaults that are overridden if the user passes any commands
CMD ["./etnblocks --enable-json-api --enable-autorefresh-option  --enable-pusher"]
