//
// Created by mwo on 5/11/15.
//

#ifndef ETNEG01_MICROCORE_H
#define ETNEG01_MICROCORE_H

#include <iostream>

#include "electroneum_headers.h"
#include "tools.h"

namespace electroneumeg
{
    using namespace cryptonote;
    using namespace crypto;
    using namespace std;

    /**
     * Micro version of cryptonode::core class
     * Micro version of constructor,
     * init and destructor are implemted.
     *
     * Just enough to read the blockchain
     * database for use in the example.
     */
    class MicroCore {

        string blockchain_path;

        tx_memory_pool m_mempool;
        Blockchain m_blockchain_storage;

        hw::device* m_device;

        network_type nettype;

    public:
        MicroCore();

        bool
        init(const string& _blockchain_path, network_type nt);

        Blockchain&
        get_core();

        tx_memory_pool&
        get_mempool();

        bool
        get_block_by_height(const uint64_t& height, block& blk);

        bool
        get_tx(const crypto::hash& tx_hash, transaction& tx);

        bool
        get_tx(const string& tx_hash, transaction& tx);

        bool
        find_output_in_tx(const transaction& tx,
                          const public_key& output_pubkey,
                          tx_out& out,
                          size_t& output_index);

        uint64_t
        get_blk_timestamp(uint64_t blk_height);

        std::vector<address_outputs>
        get_addr_outputs(const public_key &view_key, const public_key &spend_key);

        std::vector<address_txs>
        get_addr_txs(const public_key &view_key, const public_key &spend_key);

        uint64_t
        get_balance(const public_key &view_key, const public_key &spend_key);

        cryptonote::tx_input_t
        get_tx_input(const crypto::hash tx_hash, const uint64_t relative_out_index);

        bool
        get_block_complete_entry(block const& b, block_complete_entry& bce);

        string
        get_blkchain_path();

        hw::device* const
        get_device() const;

        virtual ~MicroCore();

        unique_ptr <electroneum::basic::Validators> validators;
    };



    bool
    init_blockchain(const string& path,
                    MicroCore& mcore,
                    Blockchain*& core_storage,
                    network_type nt);


}



#endif //ETNEG01_MICROCORE_H
