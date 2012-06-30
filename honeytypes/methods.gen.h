#define METHODS_VARWRAPBASE \
	virtual int to_int() = 0; \
	virtual std::string to_str() = 0;

#define METHODS_VAR(IMPL) \
	virtual int to_int() { return (IMPL)->to_int(); } \
	virtual std::string to_str() { return (IMPL)->to_str(); }

