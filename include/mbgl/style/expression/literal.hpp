#pragma once

#include <mbgl/style/expression/expression.hpp>
#include <mbgl/style/expression/parsing_context.hpp>
#include <mbgl/style/conversion.hpp>

#include <memory>

namespace mbgl {
namespace style {
namespace expression {

class Literal : public Expression {
public:
    Literal(Value value_, optional<mbgl::Value> serialized_ = optional<mbgl::Value>())
        : Expression(typeOf(value_))
        , value(value_)
        , serialized(std::move(serialized_))
    {}
    
    Literal(type::Array type_, std::vector<Value> value_, optional<mbgl::Value> serialized_ = optional<mbgl::Value>())
        : Expression(type_)
        , value(value_)
        , serialized(std::move(serialized_))
    {}

    EvaluationResult evaluate(const EvaluationContext&) const override {
        return value;
    }
    
    static ParseResult parse(const mbgl::style::conversion::Convertible&, ParsingContext&);

    void eachChild(const std::function<void(const Expression&)>&) const override {}
    
    bool operator==(const Expression& e) const override {
        if (auto rhs = dynamic_cast<const Literal*>(&e)) {
            return value == rhs->value;
        }
        return false;
    }

    std::vector<optional<Value>> possibleOutputs() const override {
        return {{ value }};
    }

    mbgl::Value serialize() const override;

    std::string getOperator() const override {
        return "literal";
    }
private:
    Value value;
    optional<mbgl::Value> serialized;
};

} // namespace expression
} // namespace style
} // namespace mbgl
