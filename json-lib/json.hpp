#ifndef SOCKETCHATROOM_JSON_H
#define SOCKETCHATROOM_JSON_H

namespace json {
    class Parser {
    private:
        std::string json_string;
    public:
        explicit Parser (std::string);
        explicit Parser (char*);
        ~Parser ();
        void parse();
        void parse (long, long);
        void get_value ();
    };
    class token;
}

#endif //SOCKETCHATROOM_JSON_H
