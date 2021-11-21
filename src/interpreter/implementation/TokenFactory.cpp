/*
Author: R. Baltrusch
*/

#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>

#include "../headers/Token.hpp"
#include "../headers/TokenFactory.hpp"

TokenFactory::TokenFactory(ConstructorMap tokens, ConstructorMap regexTokens)
    : tokens(tokens),
      regexTokens(regexTokens){};

std::shared_ptr<Token> TokenFactory::createToken(const std::string& string)
{
    ConstructorMap::iterator iterator = this->tokens.find(string);
    if (iterator != this->tokens.end())
    {
        std::any value = 0;
        int line = 1;
        std::shared_ptr<Token> token = iterator->second(value, line);
        return token;
    }

    std::stringstream messageStream;
    messageStream << "Invalid Token: " << string;
    std::string message = messageStream.str();
    throw std::invalid_argument(message);
};

Variable TokenFactory::createVariable(const std::string &name)
{
    return Variable(name);
};

Value TokenFactory::createValue(std::any &value)
{
    return Value(value);
};
