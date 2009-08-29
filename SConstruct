env = Environment();
env.MergeFlags("-lSDL -lSDL_image -lGL -llua5.1 -lluabindd");
env.MergeFlags("-g -ggdb");
env.MergeFlags("-W -Wall -pedantic");
env.MergeFlags("-I/usr/include/lua5.1");
env.Program("byna", Glob("*.cpp"));
