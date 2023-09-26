#include <iostream>
#include <string>

template <typename T>
concept ComplexConcept = requires(T t) {
    { t.hash() } -> std::convertible_to<long>;
    { t.toString() } -> std::same_as<std::string>;
        requires !std::has_virtual_destructor_v<T>;
};

// Тип удовлетворяет условию концепта
class RightType {
public:
    long hash() const { return 0; }
    std::string toString() const { return "RightType"; }
};

// Тип не удовлетворяет условию концепта, есть виртуальный деструктор
class TypeWithVirtualDestructor {
public:
    long hash() const { return 0; }
    std::string toString() const { return "TypeWithVirtualDestructor"; }
    virtual ~TypeWithVirtualDestructor() {}
};

// Тип не удовлетворяет условию концепта, метод toString() не возвращает std::string;
class TypeWithoutString {
public:
    long hash() const { return 0; }
    const char* toString() const { return "TypeWithoutString"; }
};

// Тип не удовлетворяет условию концепта, отсутствует метод hash()
class TypeWithoutHash {
public:
    std::string toString() const { return "TypeWithoutHash"; }
};

int main() {
    RightType rightObj;
    TypeWithVirtualDestructor virtualObj;
    TypeWithoutString withoutStringObj;
    TypeWithoutHash withoutHashObj;

    // Проверки
    if constexpr (ComplexConcept<RightType>) {
        std::cout << "RightType satisfies ComplexConcept." << std::endl;
    }
    else {
        std::cout << "RightType does not satisfy ComplexConcept." << std::endl;
    }

    if constexpr (ComplexConcept<TypeWithVirtualDestructor>) {
        std::cout << "TypeWithVirtualDestructor satisfies ComplexConcept." << std::endl;
    }
    else {
        std::cout << "TypeWithVirtualDestructor does not satisfy ComplexConcept." << std::endl;
    }

    if constexpr (ComplexConcept<TypeWithoutString>) {
        std::cout << "TypeWithoutString satisfies ComplexConcept." << std::endl;
    }
    else {
        std::cout << "TypeWithoutString does not satisfy ComplexConcept." << std::endl;
    }

    if constexpr (ComplexConcept<TypeWithoutHash>) {
        std::cout << "TypeWithoutHash satisfies ComplexConcept." << std::endl;
    }
    else {
        std::cout << "TypeWithoutHash does not satisfy ComplexConcept." << std::endl;
    }

    return 0;
}
