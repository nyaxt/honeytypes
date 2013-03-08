# Honeytypes

Honeytypes is a open source library, which provide dynamic primitive types in C++11.

## Sample Usage
```
Var x;
x = IntV(12345);
ht::as<int>(x) // == 12345
ht::as<std::string>(x) // == "12345"

x = StringV("TRUE");
ht::as<std::string>(x) // == "TRUE"
ht::as<bool>(x) // == true
```

## License
MIT License
