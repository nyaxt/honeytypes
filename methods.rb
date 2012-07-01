#!/usr/bin/ruby

puredecls = ["#define METHODS_VARWRAPBASE"]
relayimpls = ["#define METHODS_VAR(VIRTUAL, IMPL)"]
DATA.each_line do |decl|
  STDERR.puts "error decl: #{decl}" unless decl.match(/([\w:]+)\s+(\w+)\((.*)\)\s*(\w*)\s*;/)
  rettype = $1
  methodname = $2
  args = $3
  cv = $4
  
  args_tn = args.split(/,\s*/).map do |arg|
    arg.match(/([\w:\*]+)\s+(\w+)/)
    [$1, $2]
  end
  
  puredecls << "virtual #{rettype} #{methodname}(#{args}) #{cv} = 0;"
  
  args_namelist = args_tn.map {|t, n| n}.join(", ")
  relayimpls << "VIRTUAL #{rettype} #{methodname}(#{args}) #{cv} { return (IMPL)->#{methodname}(#{args_namelist}); }"
end

puts puredecls.join(" \\\n")
puts
puts relayimpls.join(" \\\n")

__END__
int to_int() const;
std::string to_str() const;
int cstr(char* buf, size_t len) const;
