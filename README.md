# Electroneum Blockchain Explorer

This is forked from [Onion Monero Blockchain Explorer](https://github.com/moneroexamples/onion-monero-blockchain-explorer)

# Compiling
- To compile the block explorer you need to have first compiled the main repository found [here](https://github.com/electroneum/electroneum)
- Once compiled, enter the block explorer directory and run the following commands:
  - `mkdir -p build && cd build` To create the build directory and enter it  
  - `cmake .. && make -j$(nproc)` To compile, by default the ELECTRONEUM_DIR is set to ~/electroneum
  - If you have it in a different directory then please run:
    - `cmake -D ELECTRONEUM_DIR="/path/to/electroneum/src" .. && make -j$(nproc)`

# Usage
`./etnblocks` will start the blockexplorer with default settings. Additional flags are shown below

```
  -h [ --help ] [=arg(=1)] (=0)         produce help message
  -t [ --testnet ] [=arg(=1)] (=0)      use testnet blockchain
  --enable-pusher [=arg(=1)] (=0)       enable signed transaction pusher
  --enable-mixin-details [=arg(=1)] (=0)
                                        enable mixin details for key images,
                                        e.g., timescale, mixin of mixins, in tx
                                        context
  --enable-key-image-checker [=arg(=1)] (=0)
                                        enable key images file checker
  --enable-output-key-checker [=arg(=1)] (=0)
                                        enable outputs key file checker
  --enable-json-api arg (=1)            enable JSON REST api
  --enable-tx-cache [=arg(=1)] (=0)     enable caching of transaction details
  --show-cache-times [=arg(=1)] (=0)    show times of getting data from cache
                                        vs no cache
  --enable-block-cache [=arg(=1)] (=0)  enable caching of block details
  --enable-autorefresh-option [=arg(=1)] (=0)
                                        enable users to have the index page on
                                        autorefresh
  --enable-emission-monitor [=arg(=1)] (=0)
                                        enable Electroneum total emission
                                        monitoring thread
  -p [ --port ] arg (=8081)             default explorer port
  --testnet-url arg                     you can specify testnet url, if you run
                                        it on mainnet. link will show on front
                                        page to testnet explorer
  --mainnet-url arg                     you can specify mainnet url, if you run
                                        it on testnet. link will show on front
                                        page to mainnet explorer
  --no-blocks-on-index arg (=10)        number of last blocks to be shown on
                                        index page
  --mempool-info-timeout arg (=5000)    maximum time, in milliseconds, to wait
                                        for mempool data for the front page
  --mempool-refresh-time arg (=5)       time, in seconds, for each refresh of
                                        mempool state
  -b [ --bc-path ] arg                  path to lmdb folder of the blockchain,
                                        e.g., ~/.electroneum/lmdb
  --ssl-crt-file arg                    path to crt file for ssl (https)
                                        functionality
  --ssl-key-file arg                    path to key file for ssl (https)
                                        functionality
  -d [ --deamon-url ] arg (=http:://127.0.0.1:26968)
                                        Electroneum deamon url
```
