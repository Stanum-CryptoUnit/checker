#include <eosio/multi_index.hpp>
#include <eosio/contract.hpp>
#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/time.hpp>
#include <eosio/print.hpp>
#include <eosio/system.hpp>

class [[eosio::contract]] checker : public eosio::contract {

public:
    checker( eosio::name receiver, eosio::name code, eosio::datastream<const char*> ds ): eosio::contract(receiver, code, ds)
    {}
    [[eosio::action]] void addchecksum(eosio::name username, eosio::name type, std::string checksum);
    [[eosio::action]] void rmchecksum(eosio::name username, uint64_t type);
    


    static constexpr eosio::name _me = "checker"_n; 
    static constexpr eosio::name _updater = "updater"_n;   
    


    struct [[eosio::table]] requests {
        uint64_t id;
        eosio::name type;
        eosio::time_point_sec date;
        std::string checksum;


        uint64_t primary_key() const {return id;}
        
        EOSLIB_SERIALIZE(requests, (id)(type)(date)(checksum))
    };

    typedef eosio::multi_index<"requests"_n, requests> requests_index;




private:
    void apply(uint64_t receiver, uint64_t code, uint64_t action);   
    
 
};
