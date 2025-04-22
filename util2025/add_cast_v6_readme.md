# Aggiungere (int) a set_something, non sostituire:
awk -v func_name="set_something" -v target_cast_str="(int)" -v replace_existing=0 \
    -f add_cast_v6.awk infile > outfile

# Sostituire qualsiasi cast (...) esistente in set_something con (char*):
awk -v func_name="set_something" -v target_cast_str="(char*)" -v replace_existing=1 \
    -f add_cast_v6.awk infile > outfile

# Applicare a tutti i file .c (con GNU awk):
find . -type f -name '*.c' -exec awk -i inplace \
     -v func_name="set_something" -v target_cast_str="(char*)" -v replace_existing=1 \
     -f add_cast_v6.awk {} \;
