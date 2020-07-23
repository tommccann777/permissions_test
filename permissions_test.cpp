#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract]] permissions_test : public eosio::contract {
public:
    using contract::contract;

    [[eosio::action]]
    void hasauth(name account) {
        print(has_auth(account));
    }

    [[eosio::action]]
    void reqauth(name account) {
        require_auth(account);
    }

    [[eosio::action]]
    void reqauth2(name account, name permission) {
        require_auth(permission_level(account, permission));
        eosio::print(name{account});
        eosio::print('@');
        eosio::print(name{permission});
    }

    [[eosio::action]]
    void send(name sent, name p_sent, name req) {
        action(permission_level{sent, p_sent},
               "test"_n, "reqauth"_n,
               std::make_tuple(req)
        ).send();
    }

    [[eosio::action]]
    void send2(name sent, name p_sent, name req, name p_req) {
        action(permission_level{sent, p_sent},
               "test"_n, "reqauth2"_n,
               std::make_tuple(req, p_req)
        ).send();
    }
};

// EOSIO_ABI(eosio::permissions_test, (hasauth)(reqauth)(reqauth2)(send)(send2))
