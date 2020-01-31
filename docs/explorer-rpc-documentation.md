# Block Explorer RPC Documentation

## Introduction to the JSON API

This is a list of the explorer API calls, their inputs and outputs, and examples.
The explorer has a JSON api interface. It uses conventions defined by [JSend](https://labs.omniti.com/labs/jsend).
   
### [JSON RPC Methods](#json-rpc-methods):  
* [transaction](#transaction)
* [rawtransaction](#rawtransaction)
* [block](#block)
* [transactions](#transactions)
* [mempool](#mempool)
* [search](#search)
* [networkinfo](#networkinfo)
* [outputs](#outputs)
* [outputsblocks](#outputsblocks)
* [version](#version)
* [emission](#emission) 

### **transaction**
Returns transaction data based on a provided transaction hash.

* *data*
  * *block_height*
  * *coinbase*
  * *confirmations*
  * *current_height*
  * *etn_inputs*
  * *etn_outputs*
  * *extra*
  * *inputs*
    * *amount*
    * *key_image*
    * *mixins*
      * *block_no*
      * *public_key*
  * *mixin*
  * *outputs*
    * *amount*
    * *public_key*
  * *payment_id*
  * *payment_id8*
  * *rct_type*
  * *timestamp*
  * *timestamp_utc*
  * *tx_fee*
  * *tx_hash*
  * *tx_size*
  * *tx_version*
* *status*

```bash
$ curl -X GET https://blockexplorer.electroneum.com/api/transaction/1f55eb09895fbc0a7c77bd5e22ac13c0c9fa5fc53191a5d9cb2f84b0b7120681 -H 'Content-Type: application/json'
```
```json
{
  "data": {
    "block_height":0,
    "coinbase":false,
    "confirmations":0,
    "current_height":340342,
    "etn_inputs":1257,
    "etn_outputs":1247,
    "extra":"01ababd7cb58c8ce9a2f18a0e0127af98ebe91958c1c64d5cb567d965648dcfa55",
    "inputs": [
      {
        "amount":7,
        "key_image":"9ce8b2a080ea27e1d2fcfbf98797b6917fe6906fbbf359f260f61b2cf3b29813",
        "mixins": [
          {
            "block_no":340253,
            "public_key":"3822b16c1c042c7f41d7c60b68e272a631b3a49bd18a4fa86bc6c3e5948d813c"
          }
        ]
      },
      {
        "amount":70,
        "key_image":"71d589a445061d01bf84d40465ca30178bcd7f73f95cbada5ebd24d368392396",
        "mixins": [
          {
            "block_no":338652,
            "public_key":"d9656e587548cdb5340d0e35ba8a98e2802ee62f464c5c78f8037a48e3f1b912"
          }
        ]
      },
      {
        "amount":10,
        "key_image":"ab99b79f79ac693adec03c6a6b3ea327c603298ea9eef60bad0d97cea7d1de9e",
        "mixins": [
          {
            "block_no":339644,
            "public_key":"dbedb18820d8e80d4a39f072fa4fedcda9fc46c2bb00e36c94f39626a50dfbb4"
          }
        ]
      },
      {
        "amount":100,
        "key_image":"84cac888135e823358bc0c3845497b2484774921caf26b3b49de7c87fe1e7f99",
        "mixins": [
          {
            "block_no":340253,
            "public_key":"7f2471a40cc63aa161de98ca1fcf3841016f441196d10cfef674397bece33a5f"
          }
        ]
      },
      {
        "amount":70,
        "key_image":"c0b1ac3af63a89f18d453c68820c4f060f10aeb8c8bbe28cb23017ad254d48fb",
        "mixins": [
          {
            "block_no":340253,
            "public_key":"c137e3322931614f784cf8c85db0c96b64c0c0538360c68116f7d6ab6c46094d"
          }
        ]
      },
      {
        "amount":1000,
        "key_image":"f495fd648b03cbf6a9b22c1ed8069a1fb61cd10f48b35dc8caf794ea9884e5d6",
        "mixins": [
          {
            "block_no":340253,
            "public_key":"7b2f246d83828ebadb735e94d21d597f3ad83aea9dac66cf79af6869318c907c"
          }
        ]
      }
    ],
    "mixin":1,
    "outputs": [
      {
        "amount":100,
        "public_key":"3d153cc512fde16188109151a99f567e59ac98a33a0f134452cff2d557cf4710"
      },
      {
        "amount":90,
        "public_key":"9c9b921da326ae033a278704d555a57b5a2b684d6f2bd83bd3b40633400d8ad6"
      },
      {
        "amount":1000,
        "public_key":"c5cc22df60c811ef91f56067c2cf172a55dd1ab8ac07beb8a64b4bbfc23df855"
      },
      {
        "amount":50,
        "public_key":"dc4aa3cab7e8ee46ac9f646a213ba6d12dd4b7ebbbbd7ce5dc86bbced4a60f4f"
      },
      {
        "amount":7,
        "public_key":"a93ead6a693dad06ab24efa777d55ca82e62a54e5c8ae6505bae3f14a10c5c8b"
      }
    ],
    "payment_id":"",
    "payment_id8":"",
    "rct_type":0,
    "timestamp":1532603911,
    "timestamp_utc":"2018-07-26 11:18:31",
    "tx_fee":10,
    "tx_hash":"1f55eb09895fbc0a7c77bd5e22ac13c0c9fa5fc53191a5d9cb2f84b0b7120681",
    "tx_size":824,
    "tx_version":1
  },
  "status":"success"
}
````

### **rawtransaction**
Return the raw details of a transaction based on a provided transaction hash

Outputs:

* *data*
  * *extra*
  * *signatures*
  * *unlock_time*
  * *version*
  * *vin*
    * *key*
      * *amount*
      * *k_image*
      * *key_offsets*
  * *vout*
    * *amount*
    * *target*
      * *key*
* *status*

````  
$ curl -X GET https://blockexplorer.electroneum.com/api/rawtransaction/1f55eb09895fbc0a7c77bd5e22ac13c0c9fa5fc53191a5d9cb2f84b0b7120681 -H 'Content-Type: application/json'
{
  "data": {
    "extra": [
      1,
      171,
      171,
      215,
      203,
      88,
      200,
      206,
      154,
      47,
      24,
      160,
      224,
      18,
      122,
      249,
      142,
      190,
      145,
      149,
      140,
      28,
      100,
      213,
      203,
      86,
      125,
      150,
      86,
      72,
      220,
      250,
      85
    ],
    "signatures": [
      "5bfc1683c954b8e892a7eaefd749301bee5deb4bd5ce366b87e9981981faac075a7f893d83b9c67d79d3568d860e45f2f98cafd542151410f8cf3d2c4c111c01",
      "68237f2401096892164a2022cc0fd1001853adb20d957e950fbbf84ebea0bb04e0444596b72c165a44f6373fc3e498670a0556483105f837df8adb866deac302",
      "f90b2d0004331bba283cf9998166b269f7831811d3914601ec5b5bdfefa8540ea459da47ba1bcd027983ff9bcf3eb2cbbe6e1df152c65a2c90e0b6ad5b19cc04",
      "b7c7ea55f29a250e031b40486f55d02484fe7df4f633632614c561093982a10e4db3e039cf818b43282a6f0e88e2c0cf0f845be55499688e6b900d3b84e70309",
      "16cfeae590d1511635e102d8c613f8626d1cda4957902ba58198d7413320070b713dc0e8cb141519886ee9c7a8c3f6ab810f4f94ed766f9b6f307320a369cf0f",
      "8745d9e24684a96429954d52a77c301419291cb21ef96b05a425a44f47c43808de6ed532439a943bd29157a22114dbb3a65664fbbf47846195f202db17efcf06"
    ],
    "unlock_time": 0,
    "version": 1,
    "vin": [
      {
        "key": {
          "amount": 7,
          "k_image": "9ce8b2a080ea27e1d2fcfbf98797b6917fe6906fbbf359f260f61b2cf3b29813",
          "key_offsets": [
            1223162
          ]
        }
      },
      {
        "key": {
          "amount": 70,
          "k_image": "71d589a445061d01bf84d40465ca30178bcd7f73f95cbada5ebd24d368392396",
          "key_offsets": [
            1048250
          ]
        }
      },
      {
        "key": {
          "amount": 10,
          "k_image": "ab99b79f79ac693adec03c6a6b3ea327c603298ea9eef60bad0d97cea7d1de9e",
          "key_offsets": [
            1981952
          ]
        }
      },
      {
        "key": {
          "amount": 100,
          "k_image": "84cac888135e823358bc0c3845497b2484774921caf26b3b49de7c87fe1e7f99",
          "key_offsets": [
            2833319
          ]
        }
      },
      {
        "key": {
          "amount": 70,
          "k_image": "c0b1ac3af63a89f18d453c68820c4f060f10aeb8c8bbe28cb23017ad254d48fb",
          "key_offsets": [
            1060008
          ]
        }
      },
      {
        "key": {
          "amount": 1000,
          "k_image": "f495fd648b03cbf6a9b22c1ed8069a1fb61cd10f48b35dc8caf794ea9884e5d6",
          "key_offsets": [
            9550930
          ]
        }
      }
    ],
    "vout": [
      {
        "amount": 100,
        "target": {
          "key": "3d153cc512fde16188109151a99f567e59ac98a33a0f134452cff2d557cf4710"
        }
      },
      {
        "amount": 90,
        "target": {
          "key": "9c9b921da326ae033a278704d555a57b5a2b684d6f2bd83bd3b40633400d8ad6"
        }
      },
      {
        "amount": 1000,
        "target": {
          "key": "c5cc22df60c811ef91f56067c2cf172a55dd1ab8ac07beb8a64b4bbfc23df855"
        }
      },
      {
        "amount": 50,
        "target": {
          "key": "dc4aa3cab7e8ee46ac9f646a213ba6d12dd4b7ebbbbd7ce5dc86bbced4a60f4f"
        }
      },
      {
        "amount": 7,
        "target": {
          "key": "a93ead6a693dad06ab24efa777d55ca82e62a54e5c8ae6505bae3f14a10c5c8b"
        }
      }
    ]
  },
  "status": "success"
}
````

### **block**
Return the raw details of a block for a provided block height

Outputs:

* *data*
  * *block_height*
  * *current_height*
  * *hash*
  * *size*
  * *timestamp*
  * *timestamp_utc*
  * *txs*
    * *coinbase*
    * *etn_inputs*
    * *etn_outputs*
    * *extra*
    * *mixin*
    * *payment_id*
    * *payment_id8*
    * *rct_type*
    * *tx_fee*
    * *tx_hash*
    * *tx_size*
    * *tx_version*
* *status*

````
$ curl -X GET https://blockexplorer.electroneum.com/api/block/99999 -H 'Content-Type: application/json'
{
  "data": {
    "block_height": 99999,
    "current_height": 340348,
    "hash": "7b1d9e308897f0c7c3718fd1ad61afe7381fadf9154cb751eee03d1720ead87b",
    "size": 79571,
    "timestamp": 1515225206,
    "timestamp_utc": "2018-01-06 07:53:26",
    "txs": [
      {
        "coinbase": true,
        "etn_inputs": 0,
        "etn_outputs": 728576,
        "extra": "01c1d1c86f5cb27fdc4c278c658662c05284e75e9ed2ddab5276155cf30a34118102080000000193f8aae8",
        "mixin": 0,
        "payment_id": "",
        "payment_id8": "",
        "rct_type": 0,
        "tx_fee": 0,
        "tx_hash": "a2c7a7246375e6295085ace0ab35d5749cb731668dcea5c0a141994837ef7a79",
        "tx_size": 264,
        "tx_version": 1
      },
      {
        "coinbase": false,
        "etn_inputs": 4070,
        "etn_outputs": 4069,
        "extra": "02210077b28817e0c7d7bfab3c212bd629392bd61b52d0133ef838c429f74b48fc5b2b01b5d3aa9e315d7d7af24586746aeba141719ce56bc011412c8b502a9a02c3eca9",
        "mixin": 2,
        "payment_id": "77b28817e0c7d7bfab3c212bd629392bd61b52d0133ef838c429f74b48fc5b2b",
        "payment_id8": "",
        "rct_type": 0,
        "tx_fee": 1,
        "tx_hash": "07d70f15407982a5ab666285c5fe098f434fdcd54249a9ba41f1a98d1f3e8840",
        "tx_size": 618,
        "tx_version": 1
      },
      {...}
    ]
  },
  "status": "success"
}
````

### *rawblock*
Return the raw details of a transaction based on a provided block height

Outputs:

* *data*
  * *major_version*
  * *miner_tx*
    * *extra*
    * *signatures*
    * *unlock_time*
    * *version*
    * *vin*
    * *gen*
    * *height*
    * *vout*
    * *amount*
    * *target*
    * *key*
  * *minor_version*
  * *nonce*
  * *prev_id*
  * *timestamp*
  * *tx_hashes*
* *status*

````
$ curl -X GET https://blockexplorer.electroneum.com/api/rawblock/99999 -H 'Content-Type: application/json'
{
  "data": {
    "major_version": 1,
    "miner_tx": {
      "extra": [
        1,
        193,
        209,
        200,
        111,
        92,
        178,
        127,
        220,
        76,
        39,
        140,
        101,
        134,
        98,
        192,
        82,
        132,
        231,
        94,
        158,
        210,
        221,
        171,
        82,
        118,
        21,
        92,
        243,
        10,
        52,
        17,
        129,
        2,
        8,
        0,
        0,
        0,
        1,
        147,
        248,
        170,
        232
      ],
      "signatures": [
        
      ],
      "unlock_time": 100017,
      "version": 1,
      "vin": [
        {
          "gen": {
            "height": 99999
          }
        }
      ],
      "vout": [
        {
          "amount": 6,
          "target": {
            "key": "339c95c9d298a2201cfe3fb3da45d43d295db307d62ceefc5aedc52fecd5ee5c"
          }
        },
        {
          "amount": 70,
          "target": {
            "key": "b1c696b2e78e0db2524444e3c3458622c6c23bac13b7fdb795f04db496cb288f"
          }
        },
        {
          "amount": 500,
          "target": {
            "key": "2ea254ffa551012fd985918d94d1f27569a43bd94dbd2cdeda849088e3839b09"
          }
        },
        {
          "amount": 8000,
          "target": {
            "key": "1526e586fee2984cde1e2abfdcbe3389046e720b3c88cedec1e2bc16b83b5308"
          }
        },
        {
          "amount": 20000,
          "target": {
            "key": "1036d7b4920d89516c173e4655108d8d1ba1f57cbc83c7f4ce3a72010b9fcd5b"
          }
        },
        {
          "amount": 700000,
          "target": {
            "key": "934aa1f14965e9bd6e65647491f7123ab2733a24ca339b90b7ac8200bb50c5fc"
          }
        }
      ]
    },
    "minor_version": 1,
    "nonce": 5679,
    "prev_id": "69dcb927657f4d27f734f2e31d467b971ee4bd25652a5d832fc3e26c2955555d",
    "timestamp": 1515225206,
    "tx_hashes": [
      "07d70f15407982a5ab666285c5fe098f434fdcd54249a9ba41f1a98d1f3e8840",
      "68fd41a6a90fd29cefff66a79d723f094027e18407cf7c8c05b2e49b0382c12e",
      "07187718fcb32fde83192ba7ee87d859339d8a18ef1e3d841030683d1256eb91",
      "14c7cc05daf3df1e179b17601fe1599dc5d3aee6b39faa9c4bf5530500bd417e",
      "dc30bb08dbd59f3ba43590424957300ae91cf132a4c3ce136aba623f334860e3",
      "383ae69feef1ed5988a8ef87013e828ca5e2178db5f76bcae9481f939fce66d5",
      "f087c67ae9a68ddf4b53305e036fa8f071143c5d022c087555e3d633734bf3d8",
      "d9b28580b629f66bfd13b69b74f8592682eb03ace3d3dee05ee6722266cd2e3c",
      "18d199abe4aae30fa75d715a319fe4830f14bdae0c6b89063d820f64dbbdcf63",
      "04d464a384da79bcb2c41e2c140ec0761288c3461ee3d90f04cba8c620498c14",
      "bdb0c4bad4a1244f49816497e0a73f7f52d8d17cd7adc4718a9c624703576fd6",
      "62389e820dfc0bed2aafa886ff84ba1c61fd4f12ea2e325a5319299d114521a8",
      "c0e409cbe3c87a86330522270d8325f0ce838915e2d38a9d97be094ed243d58b",
      "f42fbcd1bc112ef1394c3413053f7f38c1cde9c709a009b4802593fbf8a23acf",
      "c87b8e8892a4f833051e24c8d5d92d099784849b5f44e2692d73e5c425d9b243",
      "8a21463b10990aa3d51600c55f1b67057554465aea3903d2b2a34e5b72d91fa5",
      "c79ae3ec43fd2f031630f3f25daf622359bb9b1a7c745f761ce928ebaac44bca",
      "8a546173426b92eae1706bfc7414da15e12a06536479f0e52f2a968c57936d80",
      "497835c503249998ff0a31d88717144cf703de98f72b07adb7075bf3d22d56c0",
      "c3056ab817a11dd54e76597c8336c11d4604c7d3d3893ae197c473005ff15ead",
      "88969b12d61dc3473c48565eaeb7e91afb0bcefa89e2297ed4a4bdb687cc4a06"
    ]
  },
  "status": "success"
}
````

### *transactions*
Return the raw details of transactions in a number of blocks specified by the caller (limit).

Parameters: ?page(int),?limit(int)

Outputs:

* *data*
  * *blocks*
    * *age*
    * *hash*
    * *height*
    * *size*
    * *timestamp*
    * *timestamp_utc*
    * *txs*
      * *coinbase*
      * *etn_inputs*
      * *etn_outputs*
      * *extra*
      * *mixin*
      * *payment_id*
      * *payment_id8*
      * *rct_type*
      * *tx_fee*
      * *tx_hash*
      * *tx_size*
      * *tx_version*
  * *current_height*
  * *limit*
  * *page*
  * *total_page_no*
* *status*
  
```bash 
$ curl -X GET https://blockexplorer.electroneum.com/api/transactions?limit=1 -H 'Content-Type: application/json'
```
```json
{
  "data": {
    "blocks": [
      {
        "age": "00:00:33",
        "hash": "e6bc6f2f2da9221eab2b5dc52c0f4969e8bcebf2232303cf02c9c94b1a810f7e",
        "height": 340348,
        "size": 44028,
        "timestamp": 1532604390,
        "timestamp_utc": "2018-07-26 11:26:30",
        "txs": [
          {
            "coinbase": true,
            "etn_inputs": 0,
            "etn_outputs": 1126457,
            "extra": "01d536505e6c8453b19df1e1ab43ae0e8c1b1a23ef539e3f169aa3403b91c40e7c0208000053ffae52fdfc",
            "mixin": 0,
            "payment_id": "",
            "payment_id8": "",
            "rct_type": 0,
            "tx_fee": 0,
            "tx_hash": "19001775659ef1245532f4d0a10600402a9c58adca735f94a0886b8246b039bd",
            "tx_size": 90,
            "tx_version": 1
          },
          {
            "coinbase": false,
            "etn_inputs": 1000,
            "etn_outputs": 990,
            "extra": "01a309ba262599760ad8c3cf06b98c1deb486f2891da7c2ca5b6ac69bdfc9081c4",
            "mixin": 1,
            "payment_id": "",
            "payment_id8": "",
            "rct_type": 0,
            "tx_fee": 10,
            "tx_hash": "5a9ca2f7d236dd497b3b7348eba01668111eb9733260e71fbfabf5243ade6851",
            "tx_size": 313,
            "tx_version": 1
          },
          {...}
        ]
      }
    ],
    "current_height": 340349,
    "limit": 1,
    "page": 0,
    "total_page_no": 340349
  },
  "status": "success"
}
````

### *mempool*
Return the transactions currently sitting in the mempool. 

Parameters: ?page(int),?limit(int)

Outputs:

* *data*
  * *limit*
  * *page*
  * *total_page_no*
  * *txs*
       * *coinbase*
       * *etn_inputs*
       * *etn_outputs*
       * *extra*
       * *mixin*
       * *payment_id*
       * *payment_id8*
       * *rct_type*
       * *timestamp*
       * *timestamp_utc*
       * *tx_fee*
       * *tx_hash*
       * *tx_size*
       * *tx_version*
  * *txs_no*
* *status*
  
```bash  
$ curl -X GET https://blockexplorer.electroneum.com/api/mempool -H 'Content-Type: application/json'
```
```json
{
  "data": {
    "blocks": [
      {
        "age": "00:00:33",
        "hash": "e6bc6f2f2da9221eab2b5dc52c0f4969e8bcebf2232303cf02c9c94b1a810f7e",
        "height": 340348,
        "size": 44028,
        "timestamp": 1532604390,
        "timestamp_utc": "2018-07-26 11:26:30",
        "txs": [
          {
            "coinbase": true,
            "etn_inputs": 0,
            "etn_outputs": 1126457,
            "extra": "01d536505e6c8453b19df1e1ab43ae0e8c1b1a23ef539e3f169aa3403b91c40e7c0208000053ffae52fdfc",
            "mixin": 0,
            "payment_id": "",
            "payment_id8": "",
            "rct_type": 0,
            "tx_fee": 0,
            "tx_hash": "19001775659ef1245532f4d0a10600402a9c58adca735f94a0886b8246b039bd",
            "tx_size": 90,
            "tx_version": 1
          },
          {
            "coinbase": false,
            "etn_inputs": 1000,
            "etn_outputs": 990,
            "extra": "01a309ba262599760ad8c3cf06b98c1deb486f2891da7c2ca5b6ac69bdfc9081c4",
            "mixin": 1,
            "payment_id": "",
            "payment_id8": "",
            "rct_type": 0,
            "tx_fee": 10,
            "tx_hash": "5a9ca2f7d236dd497b3b7348eba01668111eb9733260e71fbfabf5243ade6851",
            "tx_size": 313,
            "tx_version": 1
          },
          {...}
        ]
      }
    ],
    "txs_no": 340349,
  },
  "status": "success"
}
````

### *search*
Return the raw details of a transaction or block

Parameters: height or txhash

Outputs:

* *data*
  * *block_height*
  * *current_height*
  * *hash*
  * *size*
  * *timestamp*
  * *timestamp_utc*
  * *title*
  * *txs*
    * *coinbase*
    * *etn_inputs*
    * *etn_outputs*
    * *extra*
    * *mixin*
    * *payment_id*
    * *payment_id8*
    * *rct_type*
    * *tx_fee*
    * *tx_hash*
    * *tx_size*
    * *tx_version*
* *status*

```bash
$ curl -X GET https://blockexplorer.electroneum.com/api/search/<search string> -H 'Content-Type: application/json'
```
```json
{
  "data": {
    "block_height": 340348,
    "current_height": 340349,
    "hash": "e6bc6f2f2da9221eab2b5dc52c0f4969e8bcebf2232303cf02c9c94b1a810f7e",
    "size": 44028,
    "timestamp": 1532604390,
    "timestamp_utc": "2018-07-26 11:26:30",
    "title": "block",
    "txs": [
      {
        "coinbase": true,
        "etn_inputs": 0,
        "etn_outputs": 1126457,
        "extra": "01d536505e6c8453b19df1e1ab43ae0e8c1b1a23ef539e3f169aa3403b91c40e7c0208000053ffae52fdfc",
        "mixin": 0,
        "payment_id": "",
        "payment_id8": "",
        "rct_type": 0,
        "tx_fee": 0,
        "tx_hash": "19001775659ef1245532f4d0a10600402a9c58adca735f94a0886b8246b039bd",
        "tx_size": 90,
        "tx_version": 1
      },
      {
        "coinbase": false,
        "etn_inputs": 1000,
        "etn_outputs": 990,
        "extra": "01a309ba262599760ad8c3cf06b98c1deb486f2891da7c2ca5b6ac69bdfc9081c4",
        "mixin": 1,
        "payment_id": "",
        "payment_id8": "",
        "rct_type": 0,
        "tx_fee": 10,
        "tx_hash": "5a9ca2f7d236dd497b3b7348eba01668111eb9733260e71fbfabf5243ade6851",
        "tx_size": 313,
        "tx_version": 1
      },
      {...}
    ]
  },
  "status": "success"
}
````
### *networkinfo*
Return some basic network info

Parameters: none

Outputs:

* *data*
  * *alt_block_count*
  * *block_size_limit*
  * *cumulative_difficulty*
  * *current*
  * *difficulty*
  * *fee_per_kb*
  * *grey_peerlist_size*
  * *hash_rate*
  * *height*
  * *incoming_connection_count*
  * *outgoing_connection_count*
  * *start_time*
  * *status*
  * *target*
  * *target_height*
  * *testnet*
  * *top_block_hash*
  * *tx_count*
  * *tx_pool_size*
  * *tx_pool_size_kbytes*
  * *white_peerlist_size*
* *status*

```bash
$ curl -X GET https://blockexplorer.electroneum.com/api/networkinfo -H 'Content-Type: application/json'
```
```json
{
  "data": {
    "alt_blocks_count": 89,
    "block_size_limit": 300000,
    "cumulative_difficulty": 1.2288917580777e+16,
    "current": true,
    "difficulty": 276764898767,
    "fee_per_kb": 10,
    "grey_peerlist_size": 0,
    "hash_rate": 2306374156,
    "height": 340349,
    "incoming_connections_count": 121,
    "outgoing_connections_count": 8,
    "start_time": 1530690031,
    "status": true,
    "target": 120,
    "target_height": 340216,
    "testnet": false,
    "top_block_hash": "e6bc6f2f2da9221eab2b5dc52c0f4969e8bcebf2232303cf02c9c94b1a810f7e",
    "tx_count": 4172657,
    "tx_pool_size": 78,
    "tx_pool_size_kbytes": 117565,
    "white_peerlist_size": 1000
  },
  "status": "success"
}
````

### *outputs*
Returns information about which outputs are belonging to you in a transaction for which you have specified the hash.

url: "/api/outputs" - accepts: ?txhash,?address,?viewkey,?txprove

For `txprove=0` we check which outputs belong to given address and corresponding viewkey.
For `txprove=1` we use to prove to the recipient that we sent them founds.
For this, we use recipient's address and our tx private key as a viewkey value, i.e., `viewkey=<tx_private_key>`
 
Checking outputs
 
Outputs:

* *data*
    * *address*
    * *outputs*
        * *amount*
        * *match*
        * *output_idx*
        * *output_pubkey*
    * *tx_hash*
    * *tx_prove*
    * *viewkey*
* *status*
```bash
$ curl -X GET https://blockexplorer.electroneum.com/api/outputs?txhash=28440c21f35b9dd6a521a0954f0456ee933473b1daa1e1541f1f176bbd4965c2&address=etnkPekNZr6jdQeZp6mSbUer7YpNRcuob7Y7GZnJBCZ9Ty3NpbEzTQFUFvZJmpB97JXdLphFPgkSrAHEVFq9uDY68TzfuhAknk&viewkey=0e87153e2b172c5495e1e3d88029ebf2e6f497265671ec0bf00034cf0e047e09
```
```json
{
    "data":{
        "address":"f3a5ed42b7fedabf5468827c63e245657132160836271408dc1e417214a13873cf9d6a9324a2f5f3a2d06154cdb71ab80dc4cfbf9f377b10d7114a39dbc50004",
        "outputs":[
            {
            "amount":9,
            "match":false,
            "output_idx":0,
            "output_pubkey":"f185470c76475a47943196d182b88d2ec5765dd41ab748f16b5c51e78e5f3080"
            },
            {
            "amount":50,
            "match":false,
            "output_idx":1,
            "output_pubkey":"fc3fd4b8c06accf5ef436f5d8faebb885deaf1c8b1e79b91d5613114fd01bace"
            },
            {
            "amount":1,
            "match":true,
            "output_idx":2,
            "output_pubkey":"3afd44c1a42626ad4b5eadedc199a87f855f2a22244cfd01a07251f0023a829d"
            }
        ],
        "tx_hash":"28440c21f35b9dd6a521a0954f0456ee933473b1daa1e1541f1f176bbd4965c2",
        "tx_prove":false,
        "viewkey":"0e87153e2b172c5495e1e3d88029ebf2e6f497265671ec0bf00034cf0e047e09"
    },
    "status":"success"
}
````

Proving Transfer:

We use recipient's address (i.e. not our address from which we sent etn to recipient).
For the viewkey, we use `tx_private_key` (although the GET variable is still called `viewkey`) that we obtained by sending this txs.

```bash
$ CURL -X GET https://blockexplorer.electroneum.com/api/outputs?txhash=44e9750d605d523017b98024d4858fe0b10a9ac53674d3fca47818c2275d4b4c&address=etnk1dnDsUQCNZ1ztttEGqSWuBsg7fjddQoqkNUmnkUDNyM5bq3YNj4SJFt3DvVdJNPKziq8d682EDramEhMNtKDAhBvYD15ss&viewkey=6dcb25d6658693c8c0a36237fd5fe4af49d901bc7b89c3424ce7eb71aa40710e&txprove=1
```
```json 
{
    "data":{
        "address":"30807e39ed43fc7c73ed5f5fb2988c1b14723437648e56183c86de399e835be3054c9046f3973e78c7619dc12f857cc799126b0c2b4cdaad8d955e1814ffc796",
        "outputs":[
            {"amount":10,
            "match":true,
            "output_idx":0,
            "output_pubkey":"d6360cc4ebdbae6d3e2dff105e69ae2b71d6a94c444467c42bfc97603f766b8f"
            },
            {
            "amount":8,
            "match":true,
            "output_idx":1,
            "output_pubkey":"4ccc3b04f24f10ec4836334f55340aed87e160ba1196fc376d80e87660cfeb99"
            },
            {"amount":40,
            "match":true,
            "output_idx":2,
            "output_pubkey":"172ccbbda8bcf523fa200548ff0eb1256929e267eebabe09953d02f8cc0771f8"
            }
        ],
        "tx_hash":"44e9750d605d523017b98024d4858fe0b10a9ac53674d3fca47818c2275d4b4c",
        "tx_prove":true,
        "viewkey":"6dcb25d6658693c8c0a36237fd5fe4af49d901bc7b89c3424ce7eb71aa40710e"},
    "status":"success"
}
````

### *outputsblocks*
Returns information about which outputs are belonging to you in N (=3 default) recent blocks (limit).

url: "/api/outputsblocks" - accepts: ?limit,?address,?viewkey,?mempool

Outputs

* *data*
  * *address*
  * *height*
  * *limit*
  * *mempool*
  * *outputs*
  * *viewkey*
* *status*

```` 
$ curl -X GET https://blockexplorer.electroneum.com/api/outputsblocks?address=etnkHboGpDYVCVZj5iBnvHjGqhCu5ELfFTMaESAisyEb1MuHTd5VdzcLPceHdWpdFHUJyopDn4NJpcHPNGPyUJrx3EoH2uHLQR&viewkey=c748aaf08b8e18e56c043cbe2932ce3558576d10b5c41525652eb80cf8451005&mempool=1
{
    "data":{
        "address":"be0417a36ba895f08e1dc90f86fcbbfcb4aad1d5de9d9082a3223daeb402278df5289047bd73ecb74f35efa274a346986fc24c3c85d2f0bacae080e06d3b0de8",
        "height":717169,
        "limit":"3",
        "mempool":true,
        "outputs":[],
        "viewkey":"c748aaf08b8e18e56c043cbe2932ce3558576d10b5c41525652eb80cf8451005"},
    "status":"success"
}
````

### *version*
Return version info

Parameters: none

Outputs:
* *data*
    * *api*
    * *blockchain_height*
    * *electroneum_version_full*
    * *git_branch_name*
    * *last_git_commit*
    * *last_git_commit_hash*
* *status*

```bash
$ curl -X GET https://blockexplorer.electroneum.com/api/version -H 'Content-Type: application/json'
```
```json
{
  "data": {
    "api": 65536,
    "blockchain_height": 340349,
    "electroneum_version_full": "2.0.0.0-release",
    "git_branch_name": "master",
    "last_git_commit_date": "2018-05-25",
    "last_git_commit_hash": "61d8361"
  },
  "status": "success"
}
````
api number is store as `uint32_t`. In this case `65536` represents
major version 1 and minor version 0.
In JavaScript to get these numbers, one can do as follows:

```javascript
var api_major = response.data.api >> 16;
var api_minor = response.data.api & 0xffff;
```     

### *emission*
Returns current emission statistics

Outputs

* *data*
  * *blk_no*
  * *coinbase*
  * *fee*
* *status*

```bash
curl -X GET http://blockexplorer.electroneum.com/api/emission
```

```json
{
  "data": {
    "blk_no": 1313969,
    "coinbase": 14489473877253413000,
    "fee": 52601974988641130
  },
  "status": "success"
}
```