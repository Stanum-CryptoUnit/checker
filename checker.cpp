
#include "checker.hpp"


using namespace eosio;


  [[eosio::action]] void checker::addchecksum(eosio::name username, eosio::name type, std::string checksum){
    
    eosio::check(has_auth(username) || has_auth(_updater), "missing required authority");
    auto payer =  has_auth(_updater) ? _updater : username;

    requests_index requests(_me, username.value);
    requests.emplace(payer, [&](auto &r){
      r.id = requests.available_primary_key();
      r.type = type;
      r.date = eosio::time_point_sec(eosio::current_time_point().sec_since_epoch());;
      r.checksum = checksum;
    });
    print("ok");
  }

[[eosio::action]] void checker::rmchecksum(eosio::name username, uint64_t id){
    require_auth(_updater);

    requests_index requests(_me, username.value);
    auto request = requests.find(id);
    requests.erase(request);

  }



extern "C" {
   
   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        if (code == checker::_me.value) {
          if (action == "addchecksum"_n.value){
            execute_action(name(receiver), name(code), &checker::addchecksum);
          } else if (action == "rmchecksum"_n.value){
            execute_action(name(receiver), name(code), &checker::rmchecksum);
          }             
        } else {
          if (action == "transfer"_n.value){
            
            struct transfer{
                eosio::name from;
                eosio::name to;
                eosio::asset quantity;
                std::string memo;
            };

            auto op = eosio::unpack_action_data<transfer>();

            if (op.to == checker::_me){
              //DISPATCHER FOR INCOME TRANSFERS 
            }
          }
        }
  };
};
