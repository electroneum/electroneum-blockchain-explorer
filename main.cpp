#define CROW_ENABLE_SSL


#include "src/page.h"

#include "ext/crow/crow.h"
#include "src/CmdLineOptions.h"
#include "src/MicroCore.h"

#include <fstream>
#include <regex>

using boost::filesystem::path;
using electroneumeg::remove_bad_chars;

using namespace std;

namespace myetn
{
struct htmlresponse: public crow::response
{
    htmlresponse(string&& _body)
            : crow::response {std::move(_body)}
    {
        add_header("Content-Type", "text/html; charset=utf-8");
    }
};

struct jsonresponse: public crow::response
{
    jsonresponse(const nlohmann::json& _body)
            : crow::response {_body.dump()}
    {
        add_header("Access-Control-Allow-Origin", "*");
        add_header("Access-Control-Allow-Headers", "Content-Type");
        add_header("Content-Type", "application/json");
    }
};
}

int
main(int ac, const char* av[])
{
    // get command line options
    electroneumeg::CmdLineOptions opts {ac, av};

    auto help_opt                      = opts.get_option<bool>("help");

    // if help was chosen, display help text and finish
    if (*help_opt)
    {
        return EXIT_SUCCESS;
    }

    auto port_opt                      = opts.get_option<string>("port");
    auto bindaddr_opt                  = opts.get_option<string>("bindaddr");
    auto bc_path_opt                   = opts.get_option<string>("bc-path");
    auto deamon_url_opt                = opts.get_option<string>("deamon-url");
    auto ssl_crt_file_opt              = opts.get_option<string>("ssl-crt-file");
    auto ssl_key_file_opt              = opts.get_option<string>("ssl-key-file");
    auto no_blocks_on_index_opt        = opts.get_option<string>("no-blocks-on-index");
    auto testnet_url                   = opts.get_option<string>("testnet-url");
    auto stagenet_url                  = opts.get_option<string>("stagenet-url");
    auto mainnet_url                   = opts.get_option<string>("mainnet-url");
    auto mempool_info_timeout_opt      = opts.get_option<string>("mempool-info-timeout");
    auto mempool_refresh_time_opt      = opts.get_option<string>("mempool-refresh-time");
    auto testnet_opt                   = opts.get_option<bool>("testnet");
    auto stagenet_opt                  = opts.get_option<bool>("stagenet");
    auto enable_key_image_checker_opt  = opts.get_option<bool>("enable-key-image-checker");
    auto enable_output_key_checker_opt = opts.get_option<bool>("enable-output-key-checker");
    auto enable_autorefresh_option_opt = opts.get_option<bool>("enable-autorefresh-option");
    auto enable_pusher_opt             = opts.get_option<bool>("enable-pusher");
    auto enable_js_opt                 = opts.get_option<bool>("enable-js");
    auto enable_mixin_details_opt      = opts.get_option<bool>("enable-mixin-details");
    auto enable_json_api_opt           = opts.get_option<bool>("enable-json-api");
    auto enable_as_hex_opt             = opts.get_option<bool>("enable-as-hex");
    auto enable_tx_cache_opt           = opts.get_option<bool>("enable-tx-cache");
    auto concurrency_opt               = opts.get_option<size_t>("concurrency");
    auto enable_block_cache_opt        = opts.get_option<bool>("enable-block-cache");
    auto show_cache_times_opt          = opts.get_option<bool>("show-cache-times");
    auto enable_emission_monitor_opt   = opts.get_option<bool>("enable-emission-monitor");



    bool testnet                      {*testnet_opt};
    bool stagenet                     {*stagenet_opt};

    if (testnet && stagenet)
    {
        cerr << "testnet and stagenet cannot be specified at the same time!" << endl;
        return EXIT_FAILURE;
    }

    const cryptonote::network_type nettype = testnet ?
        cryptonote::network_type::TESTNET : stagenet ?
        cryptonote::network_type::STAGENET : cryptonote::network_type::MAINNET;

    bool enable_pusher                {*enable_pusher_opt};
    bool enable_js                    {*enable_js_opt};
    bool enable_key_image_checker     {*enable_key_image_checker_opt};
    bool enable_autorefresh_option    {*enable_autorefresh_option_opt};
    bool enable_output_key_checker    {*enable_output_key_checker_opt};
    bool enable_mixin_details         {*enable_mixin_details_opt};
    bool enable_json_api              {*enable_json_api_opt};
    bool enable_as_hex                {*enable_as_hex_opt};
    bool enable_tx_cache              {*enable_tx_cache_opt};
    bool enable_block_cache           {*enable_block_cache_opt};
    bool enable_emission_monitor      {*enable_emission_monitor_opt};
    bool show_cache_times             {*show_cache_times_opt};

    // set  electroneum log output level
    uint32_t log_level = 0;
    mlog_configure("", true);

    (void) log_level;

    //cast port number in string to uint
    uint16_t app_port = boost::lexical_cast<uint16_t>(*port_opt);

    string bindaddr = *bindaddr_opt;

    // cast no_blocks_on_index_opt to uint
    uint64_t no_blocks_on_index = boost::lexical_cast<uint64_t>(*no_blocks_on_index_opt);

    bool use_ssl {false};

    string ssl_crt_file;
    string ssl_key_file;

    // check if ssl enabled and files exist

    if (ssl_crt_file_opt and ssl_key_file_opt)
    {
        if (!boost::filesystem::exists(boost::filesystem::path(*ssl_crt_file_opt)))
        {
            cerr << "ssl_crt_file path: " << *ssl_crt_file_opt
                 << "does not exist!" << endl;

            return EXIT_FAILURE;
        }

        if (!boost::filesystem::exists(boost::filesystem::path(*ssl_key_file_opt)))
        {
            cerr << "ssl_key_file path: " << *ssl_key_file_opt
                 << "does not exist!" << endl;

            return EXIT_FAILURE;
        }

        ssl_crt_file = *ssl_crt_file_opt;
        ssl_key_file = *ssl_key_file_opt;

        use_ssl = true;
    }



    // get blockchain path
    path blockchain_path;

    if (!electroneumeg::get_blockchain_path(bc_path_opt, blockchain_path, nettype))
    {
        cerr << "Error getting blockchain path." << endl;
        return EXIT_FAILURE;
    }

    cout << blockchain_path << endl;


    // create instance of our MicroCore
    // and make pointer to the Blockchain
    electroneumeg::MicroCore mcore;
    cryptonote::Blockchain* core_storage;

    // initialize mcore and core_storage
    if (!electroneumeg::init_blockchain(blockchain_path.string(),
                               mcore, core_storage, nettype))
    {
        cerr << "Error accessing blockchain." << endl;
        return EXIT_FAILURE;
    }

    string deamon_url {*deamon_url_opt};

    if (testnet && deamon_url == "http:://127.0.0.1:26968")
        deamon_url = "http:://127.0.0.1:36968";
    if (stagenet && deamon_url == "http:://127.0.0.1:26968")
        deamon_url = "http:://127.0.0.1:38081";

    uint64_t mempool_info_timeout {5000};

    try
    {
        mempool_info_timeout = boost::lexical_cast<uint64_t>(
                *mempool_info_timeout_opt);
    }
    catch (boost::bad_lexical_cast &e)
    {
        cout << "Cant cast " << (*mempool_info_timeout_opt) 
             <<" into numbers. Using default values.\n";
    }

    uint64_t mempool_refresh_time {10};


    if (enable_emission_monitor == true)
    {
        // This starts new thread, which aim is
        // to calculate, store and monitor
        // current total Electroneum emission amount.

        // This thread stores the current emission
        // which it has caluclated in
        // <blockchain_path>/emission_amount.txt file,
        // e.g., ~/.electroneum/lmdb/emission_amount.txt.
        // So instead of calcualting the emission
        // from scrach whenever the explorer is started,
        // the thread is initalized with the values
        // found in emission_amount.txt file.

        electroneumeg::CurrentBlockchainStatus::blockchain_path
                = blockchain_path;
        electroneumeg::CurrentBlockchainStatus::nettype
                = nettype;
        electroneumeg::CurrentBlockchainStatus::deamon_url
                = deamon_url;
        electroneumeg::CurrentBlockchainStatus::set_blockchain_variables(
                &mcore, core_storage);

        // launch the status monitoring thread so that it keeps track of blockchain
        // info, e.g., current height. Information from this thread is used
        // by tx searching threads that are launched for each user independently,
        // when they log back or create new account.
        electroneumeg::CurrentBlockchainStatus::start_monitor_blockchain_thread();
    }


    electroneumeg::MempoolStatus::blockchain_path
            = blockchain_path;
    electroneumeg::MempoolStatus::nettype
            = nettype;
    electroneumeg::MempoolStatus::deamon_url
            = deamon_url;
    electroneumeg::MempoolStatus::set_blockchain_variables(
            &mcore, core_storage);

    electroneumeg::MempoolStatus::network_info initial_info;
    strcpy(initial_info.block_size_limit_str, "0.0");
    strcpy(initial_info.block_size_median_str, "0.0");
    electroneumeg::MempoolStatus::current_network_info = initial_info;

    try
    {
        mempool_refresh_time = boost::lexical_cast<uint64_t>(*mempool_refresh_time_opt);

    }
    catch (boost::bad_lexical_cast &e)
    {
        cout << "Cant cast " << (*mempool_refresh_time_opt)
             <<" into number. Using default value."
             << endl;
    }

    // launch the status monitoring thread so that it keeps track of blockchain
    // info, e.g., current height. Information from this thread is used
    // by tx searching threads that are launched for each user independently,
    // when they log back or create new account.
    electroneumeg::MempoolStatus::mempool_refresh_time = mempool_refresh_time;
    electroneumeg::MempoolStatus::start_mempool_status_thread();

    // create instance of page class which
    // contains logic for the website
    electroneumeg::page etnblocks(&mcore,
                          core_storage,
                          deamon_url,
                          nettype,
                          enable_pusher,
                          enable_js,
                          enable_as_hex,
                          enable_key_image_checker,
                          enable_output_key_checker,
                          enable_autorefresh_option,
                          enable_mixin_details,
                          enable_tx_cache,
                          enable_block_cache,
                          show_cache_times,
                          no_blocks_on_index,
                          mempool_info_timeout,
                          *testnet_url,
                          *stagenet_url,
                          *mainnet_url);

    // crow instance
    crow::SimpleApp app;

    // get domian url based on the request
    auto get_domain = [&use_ssl](crow::request const& req) {
        return (use_ssl ? "https://" : "http://")
               + req.get_header_value("Host");
    };

    CROW_ROUTE(app, "/")
    ([&]() {
        return myetn::htmlresponse(etnblocks.index2());
    });

    CROW_ROUTE(app, "/page/<uint>")
    ([&](size_t page_no) {
        return myetn::htmlresponse(etnblocks.index2(page_no));
    });

    CROW_ROUTE(app, "/block/<uint>")
    ([&](size_t block_height) {
        return myetn::htmlresponse(etnblocks.show_block(block_height));
    });

    CROW_ROUTE(app, "/block/<uint>/page/<uint>")
    ([&](size_t block_height, size_t page_no) {
        return myetn::htmlresponse(etnblocks.show_block(block_height, page_no));
    });

    CROW_ROUTE(app, "/block/<string>")
    ([&](string block_hash) {
        return myetn::htmlresponse(
                etnblocks.show_block(remove_bad_chars(block_hash)));
    });

    CROW_ROUTE(app, "/block/<string>/page/<uint>")
    ([&](string block_hash, size_t page_no) {
        return myetn::htmlresponse(
                etnblocks.show_block(remove_bad_chars(block_hash), page_no));
    });

    CROW_ROUTE(app, "/tx/<string>")
    ([&](string tx_hash) {
        return myetn::htmlresponse(
                etnblocks.show_tx(remove_bad_chars(tx_hash)));
    });
    if (enable_autorefresh_option)
    {
        CROW_ROUTE(app, "/tx/<string>/autorefresh")
        ([&](string tx_hash) {
            bool refresh_page {true};
            uint16_t with_ring_signatures {0};
            return myetn::htmlresponse(
                etnblocks.show_tx(remove_bad_chars(tx_hash), with_ring_signatures, refresh_page));
        });
    }

    if (enable_as_hex)
    {
        CROW_ROUTE(app, "/txhex/<string>")
        ([&](string tx_hash) {
            return crow::response(
                    etnblocks.show_tx_hex(remove_bad_chars(tx_hash)));
        });

        CROW_ROUTE(app, "/ringmembershex/<string>")
        ([&](string tx_hash) {
            return crow::response(
                    etnblocks.show_ringmembers_hex(remove_bad_chars(tx_hash)));
        });

        CROW_ROUTE(app, "/blockhex/<uint>")
        ([&](size_t block_height) {
            return crow::response(
                    etnblocks.show_block_hex(block_height, false));
        });

        CROW_ROUTE(app, "/blockhexcomplete/<uint>")
        ([&](size_t block_height) {
            return crow::response(
                    etnblocks.show_block_hex(block_height, true));
        });

//        CROW_ROUTE(app, "/ringmemberstxhex/<string>")
//        ([&](string tx_hash) {
//            return crow::response(
//              etnblocks.show_ringmemberstx_hex(remove_bad_chars(tx_hash)));
//        });

        CROW_ROUTE(app, "/ringmemberstxhex/<string>")
        ([&](string tx_hash) {
            return myetn::jsonresponse {
                etnblocks.show_ringmemberstx_jsonhex(
                        remove_bad_chars(tx_hash))};
        });

    }

    CROW_ROUTE(app, "/tx/<string>/<uint>")
    ([&](string tx_hash, uint16_t with_ring_signatures)
     {
        return myetn::htmlresponse(
                etnblocks.show_tx(remove_bad_chars(tx_hash), 
                    with_ring_signatures));
    });
    if (enable_autorefresh_option)
    {
        CROW_ROUTE(app, "/tx/<string>/<uint>/autorefresh")
        ([&](string tx_hash, uint16_t with_ring_signature) {
            bool refresh_page {true};
            return myetn::htmlresponse(
                etnblocks.show_tx(remove_bad_chars(tx_hash), with_ring_signature, refresh_page));
        });
    }

    CROW_ROUTE(app, "/myoutputs").methods("POST"_method)
    ([&](const crow::request& req) -> myetn::htmlresponse
     {

        map<std::string, std::string> post_body
                = electroneumeg::parse_crow_post_data(req.body);

        if (post_body.count("etn_address") == 0
            || post_body.count("viewkey") == 0
            || post_body.count("tx_hash") == 0)
        {
            return string("etn address, viewkey or tx hash not provided");
        }

        string tx_hash     = remove_bad_chars(post_body["tx_hash"]);
        string etn_address = remove_bad_chars(post_body["etn_address"]);
        string viewkey     = remove_bad_chars(post_body["viewkey"]);

        // this will be only not empty when checking raw tx data
        // using tx pusher
        string raw_tx_data = remove_bad_chars(post_body["raw_tx_data"]);

        string domain      =  get_domain(req);

        string response = etnblocks.show_my_outputs(
                                         tx_hash, etn_address,
                                         viewkey, raw_tx_data,
                                         domain);

        return myetn::htmlresponse(std::move(response));
    });

    CROW_ROUTE(app, "/myoutputs/<string>/<string>/<string>")
    ([&](const crow::request& req, string tx_hash,
        string etn_address, string viewkey)
     {

        string domain = get_domain(req);

        return myetn::htmlresponse(etnblocks.show_my_outputs(
                                         remove_bad_chars(tx_hash),
                                         remove_bad_chars(etn_address),
                                         remove_bad_chars(viewkey),
                                         string {},
                                         domain));
    });

    CROW_ROUTE(app, "/prove").methods("POST"_method)
        ([&](const crow::request& req) -> myetn::htmlresponse 
         {

            map<std::string, std::string> post_body
                    = electroneumeg::parse_crow_post_data(req.body);

            if (post_body.count("etnaddress") == 0
                || post_body.count("txprvkey") == 0
                || post_body.count("txhash") == 0)
            {
                return string("etn address, tx private key or "
                                      "tx hash not provided");
            }

            string tx_hash     = remove_bad_chars(post_body["txhash"]);
            string tx_prv_key  = remove_bad_chars(post_body["txprvkey"]);
            string etn_address = remove_bad_chars(post_body["etnaddress"]);

            // this will be only not empty when checking raw tx data
            // using tx pusher
            string raw_tx_data = remove_bad_chars(post_body["raw_tx_data"]);

            string domain      = get_domain(req);

            return myetn::htmlresponse(etnblocks.show_prove(tx_hash,
                                        etn_address,
                                        tx_prv_key,
                                        raw_tx_data,
                                        domain));
    });


    CROW_ROUTE(app, "/prove/<string>/<string>/<string>")
    ([&](const crow::request& req, string tx_hash,
         string etn_address, string tx_prv_key) 
     {

        string domain = get_domain(req);

        return myetn::htmlresponse(etnblocks.show_prove(
                                    remove_bad_chars(tx_hash),
                                    remove_bad_chars(etn_address),
                                    remove_bad_chars(tx_prv_key),
                                    string {},
                                    domain));
    });

    if (enable_pusher)
    {
        CROW_ROUTE(app, "/rawtx")
        ([&]() {
            return myetn::htmlresponse(etnblocks.show_rawtx());
        });

        CROW_ROUTE(app, "/checkandpush").methods("POST"_method)
        ([&](const crow::request& req) -> myetn::htmlresponse
         {

            map<std::string, std::string> post_body
                    = electroneumeg::parse_crow_post_data(req.body);

            if (post_body.count("rawtxdata") == 0 
                    || post_body.count("action") == 0)
            {
                return string("Raw tx data or action not provided");
            }

            string raw_tx_data = remove_bad_chars(post_body["rawtxdata"]);
            string action      = remove_bad_chars(post_body["action"]);

            if (action == "check")
                return myetn::htmlresponse(
                        etnblocks.show_checkrawtx(raw_tx_data, action));
            else if (action == "push")
                return myetn::htmlresponse(
                        etnblocks.show_pushrawtx(raw_tx_data, action));
            return string("Provided action is neither check nor push");

        });
    }

    if (enable_key_image_checker)
    {
        CROW_ROUTE(app, "/rawkeyimgs")
        ([&]() {
            return myetn::htmlresponse(etnblocks.show_rawkeyimgs());
        });

        CROW_ROUTE(app, "/checkrawkeyimgs").methods("POST"_method)
        ([&](const crow::request& req) -> myetn::htmlresponse
         {

            map<std::string, std::string> post_body
                    = electroneumeg::parse_crow_post_data(req.body);

            if (post_body.count("rawkeyimgsdata") == 0)
            {
                return string("Raw key images data not given");
            }

            if (post_body.count("viewkey") == 0)
            {
                return string("Viewkey not provided. Cant decrypt key image file without it");
            }

            string raw_data = remove_bad_chars(post_body["rawkeyimgsdata"]);
            string viewkey  = remove_bad_chars(post_body["viewkey"]);

            return myetn::htmlresponse(
                    etnblocks.show_checkrawkeyimgs(raw_data, viewkey));
        });
    }


    if (enable_output_key_checker)
    {
        CROW_ROUTE(app, "/rawoutputkeys")
        ([&]() {
            return myetn::htmlresponse(etnblocks.show_rawoutputkeys());
        });

        CROW_ROUTE(app, "/checkrawoutputkeys").methods("POST"_method)
        ([&](const crow::request& req) -> myetn::htmlresponse
         {

            map<std::string, std::string> post_body
                    = electroneumeg::parse_crow_post_data(req.body);

            if (post_body.count("rawoutputkeysdata") == 0)
            {
                return string("Raw output keys data not given");
            }

            if (post_body.count("viewkey") == 0)
            {
                return string("Viewkey not provided. Cant decrypt "
                                      "key image file without it");
            }

            string raw_data = remove_bad_chars(post_body["rawoutputkeysdata"]);
            string viewkey  = remove_bad_chars(post_body["viewkey"]);

            return myetn::htmlresponse(
                    etnblocks.show_checkcheckrawoutput(raw_data, viewkey));
        });
    }


    CROW_ROUTE(app, "/search").methods("GET"_method)
    ([&](const crow::request& req) {
        return myetn::htmlresponse(
                etnblocks.search(
                    remove_bad_chars(
                        string(req.url_params.get("value")))));
    });

    CROW_ROUTE(app, "/mempool")
    ([&]() {
        return myetn::htmlresponse(etnblocks.mempool(true));
    });

    // alias to  "/mempool"
    CROW_ROUTE(app, "/txpool")
    ([&]() {
        return myetn::htmlresponse(etnblocks.mempool(true));
    });

    CROW_ROUTE(app, "/address/<string>")
    ([&](string address) -> myetn::htmlresponse
     {

         address = remove_bad_chars(address);
         // parse string representing given electroneum address
         cryptonote::address_parse_info address_info;

         cryptonote::network_type nettype_addr {cryptonote::network_type::MAINNET};

         if (!electroneumeg::parse_str_address(address, address_info, nettype_addr))
         {
           cerr << "Cant parse string address: " << address << endl;
           return string("Cant parse address (probably incorrect format): ")
                  + address;
         }
         return myetn::htmlresponse(etnblocks.show_address_details(address_info));
     });

    CROW_ROUTE(app, "/address/<string>/page/<uint>")
    ([&](string address, size_t page_no) -> myetn::htmlresponse
     {

        address = remove_bad_chars(address);
         // parse string representing given electroneum address
         cryptonote::address_parse_info address_info;

         cryptonote::network_type nettype_addr {cryptonote::network_type::MAINNET};

         if (!electroneumeg::parse_str_address(address, address_info, nettype_addr))
         {
           cerr << "Cant parse string address: " << address << endl;
           return string("Cant parse address (probably incorrect format): ")
                  + address;
         }
         return myetn::htmlresponse(etnblocks.show_address_details(address_info, nettype_addr, page_no));
     });

//    CROW_ROUTE(app, "/altblocks")
//    ([&](const crow::request& req) {
//        return etnblocks.altblocks();
//    });

    CROW_ROUTE(app, "/robots.txt")
    ([&]() {
        string text = "User-agent: *\n"
                      "Disallow: ";
        return text;
    });

    CROW_ROUTE(app, "/css/<string>")
    ([&](std::string css) {
        return electroneumeg::read("./templates/css/" + css);
    });

    CROW_ROUTE(app, "/imgs/<string>")
    ([&](std::string img) {
        return electroneumeg::read("./templates/imgs/" + img);
    });

    CROW_ROUTE(app, "/fonts/<string>")
    ([&](std::string font) {
        return electroneumeg::read("./templates/fonts/" + font);
    });

    if (enable_js)
    {
        cout << "Enable JavaScript checking of outputs and proving txs\n";

        CROW_ROUTE(app, "/js/jquery.min.js")
        ([&]() {
            return etnblocks.get_js_file("jquery.min.js");
        });

        CROW_ROUTE(app, "/js/crc32.js")
        ([&]() {
            return etnblocks.get_js_file("crc32.js");
        });

        CROW_ROUTE(app, "/js/biginteger.js")
        ([&]() {
            return etnblocks.get_js_file("biginteger.js");
        });

        CROW_ROUTE(app, "/js/crypto.js")
        ([&]() {
            return etnblocks.get_js_file("crypto.js");
        });

        CROW_ROUTE(app, "/js/config.js")
        ([&]() {
            return etnblocks.get_js_file("config.js");
        });

        CROW_ROUTE(app, "/js/nacl-fast-cn.js")
        ([&]() {
            return etnblocks.get_js_file("nacl-fast-cn.js");
        });

        CROW_ROUTE(app, "/js/base58.js")
        ([&]() {
            return etnblocks.get_js_file("base58.js");
        });

        CROW_ROUTE(app, "/js/cn_util.js")
        ([&]() {
            return etnblocks.get_js_file("cn_util.js");
        });

        CROW_ROUTE(app, "/js/sha3.js")
        ([&]() {
            return etnblocks.get_js_file("sha3.js");
        });

        CROW_ROUTE(app, "/js/all_in_one.js")
        ([&]() {
            // /js/all_in_one.js file does not exist. it is generated on the fly
            // from the above real files.
            return etnblocks.get_js_file("all_in_one.js");
        });

    } // if (enable_js)

    if (enable_json_api)
    {

        cout << "Enable JSON API\n";

        CROW_ROUTE(app, "/api/transaction/<string>")
        ([&](string tx_hash) {

            myetn::jsonresponse r{etnblocks.json_transaction(remove_bad_chars(tx_hash))};

            return r;
        });

        CROW_ROUTE(app, "/api/rawtransaction/<string>")
        ([&](string tx_hash) {

            myetn::jsonresponse r{etnblocks.json_rawtransaction(remove_bad_chars(tx_hash))};

            return r;
        });

        CROW_ROUTE(app, "/api/detailedtransaction/<string>")
        ([&](string tx_hash) {

            myetn::jsonresponse r{etnblocks.json_detailedtransaction(remove_bad_chars(tx_hash))};

            return r;
        });

        CROW_ROUTE(app, "/api/block/<string>")
        ([&](string block_no_or_hash) {

            myetn::jsonresponse r{etnblocks.json_block(remove_bad_chars(block_no_or_hash))};

            return r;
        });

        CROW_ROUTE(app, "/api/rawblock/<string>")
        ([&](string block_no_or_hash) {

            myetn::jsonresponse r{etnblocks.json_rawblock(remove_bad_chars(block_no_or_hash))};

            return r;
        });

        CROW_ROUTE(app, "/api/transactions").methods("GET"_method)
        ([&](const crow::request &req) {

            string page = regex_search(req.raw_url, regex {"page=\\d+"}) ?
                          req.url_params.get("page") : "0";

            string limit = regex_search(req.raw_url, regex {"limit=\\d+"}) ?
                           req.url_params.get("limit") : "25";

            myetn::jsonresponse r{etnblocks.json_transactions(
                    remove_bad_chars(page), remove_bad_chars(limit))};

            return r;
        });

        CROW_ROUTE(app, "/api/mempool").methods("GET"_method)
        ([&](const crow::request &req) {

            string page = regex_search(req.raw_url, regex {"page=\\d+"}) ?
                          req.url_params.get("page") : "0";

            // default value for limit is some large number, so that
            // a call to api/mempool without any limit return all
            // mempool txs
            string limit = regex_search(req.raw_url, regex {"limit=\\d+"}) ?
                           req.url_params.get("limit") : "100000000";

            myetn::jsonresponse r{etnblocks.json_mempool(
                    remove_bad_chars(page), remove_bad_chars(limit))};

            return r;
        });

        CROW_ROUTE(app, "/api/search/<string>")
        ([&](string search_value) {

            myetn::jsonresponse r{etnblocks.json_search(remove_bad_chars(search_value))};

            return r;
        });

        CROW_ROUTE(app, "/api/networkinfo")
        ([&]() {

            myetn::jsonresponse r{etnblocks.json_networkinfo()};

            return r;
        });

        CROW_ROUTE(app, "/api/emission")
        ([&]() {

            myetn::jsonresponse r{etnblocks.json_emission()};

            return r;
        });

        CROW_ROUTE(app, "/api/outputs").methods("GET"_method)
        ([&](const crow::request &req) {

            string tx_hash = regex_search(req.raw_url, regex {"txhash=\\w+"}) ?
                             req.url_params.get("txhash") : "";

            string address = regex_search(req.raw_url, regex {"address=\\w+"}) ?
                             req.url_params.get("address") : "";

            string viewkey = regex_search(req.raw_url, regex {"viewkey=\\w+"}) ?
                             req.url_params.get("viewkey") : "";

            bool tx_prove{false};

            try
            {
                tx_prove = regex_search(req.raw_url, regex {"txprove=[01]"}) ?
                           boost::lexical_cast<bool>(req.url_params.get("txprove")) :
                           false;
            }
            catch (const boost::bad_lexical_cast &e)
            {
                cerr << "Cant parse tx_prove as bool. Using default value" << endl;
            }

            myetn::jsonresponse r{etnblocks.json_outputs(
                    remove_bad_chars(tx_hash),
                    remove_bad_chars(address),
                    remove_bad_chars(viewkey),
                    tx_prove)};

            return r;
        });

        CROW_ROUTE(app, "/api/outputsblocks").methods("GET"_method)
        ([&](const crow::request &req) {

            string limit = regex_search(req.raw_url, regex {"limit=\\d+"}) ?
                           req.url_params.get("limit") : "3";

            string address = regex_search(req.raw_url, regex {"address=\\w+"}) ?
                             req.url_params.get("address") : "";

            string viewkey = regex_search(req.raw_url, regex {"viewkey=\\w+"}) ?
                             req.url_params.get("viewkey") : "";

            bool in_mempool_aswell {false};

            try
            {
                in_mempool_aswell = regex_search(
                        req.raw_url, regex {"mempool=[01]"}) ?
                           boost::lexical_cast<bool>(
                                   req.url_params.get("mempool")) :
                           false;
            }
            catch (const boost::bad_lexical_cast &e)
            {
                cerr << "Cant parse tx_prove as bool. Using default value" 
                     << endl;
            }

            myetn::jsonresponse r{etnblocks.json_outputsblocks(
                    remove_bad_chars(limit),
                    remove_bad_chars(address),
                    remove_bad_chars(viewkey),
                    in_mempool_aswell)};

            return r;
        });

        CROW_ROUTE(app, "/api/version")
        ([&]() {

            myetn::jsonresponse r{etnblocks.json_version()};

            return r;
        });

    } // if (enable_json_api)

    if (enable_autorefresh_option)
    {
        CROW_ROUTE(app, "/autorefresh")
        ([&]() {
            uint64_t page_no {0};
            bool refresh_page {true};
            return etnblocks.index2(page_no, refresh_page);
        });
    }

    // run the crow http server

    if (use_ssl)
    {
        cout << "Staring in ssl mode" << endl;
        app.bindaddr(bindaddr).port(app_port).ssl_file(
                ssl_crt_file, ssl_key_file)
                .multithreaded().run();
    }
    else
    {
        cout << "Staring in non-ssl mode" << endl;
        if (*concurrency_opt == 0)
        {
            app.bindaddr(bindaddr).port(app_port).multithreaded().run();
        }
        else
        {
            app.bindaddr(bindaddr).port(app_port)
                .concurrency(*concurrency_opt).run();
        }
    }

    if (enable_emission_monitor == true)
    {
        // finish Emission monitoring thread in a cotrolled manner.

        cout << "Waiting for emission monitoring thread to finish." << endl;

        electroneumeg::CurrentBlockchainStatus::m_thread.interrupt();
        electroneumeg::CurrentBlockchainStatus::m_thread.join();

        cout << "Emission monitoring thread finished." << endl;
    }

    // finish mempool thread

    cout << "Waiting for mempool monitoring thread to finish." << endl;

    electroneumeg::MempoolStatus::m_thread.interrupt();
    electroneumeg::MempoolStatus::m_thread.join();

    cout << "Mempool monitoring thread finished." << endl;

    cout << "The explorer is terminating." << endl;

    return EXIT_SUCCESS;
}
