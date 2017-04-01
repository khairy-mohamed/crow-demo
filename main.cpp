#include "crow_all.h"

int main() {
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    CROW_ROUTE(app, "/")
            ([] {
                crow::mustache::context ctx;
                ctx["message"] = "Hello World!";
                return crow::mustache::load("index.html").render(ctx);
            });

    CROW_ROUTE(app, "/api/accounts/<int>")
            ([](int id) {
                crow::json::wvalue account;
                account["id"] = id;
                account["name"] = "name" + std::to_string(id);
                return account;
            });

//    crow::logger::setLogLevel(crow::LogLevel::DEBUG);

    app.port(8080)
            .multithreaded()
            .run();
}
