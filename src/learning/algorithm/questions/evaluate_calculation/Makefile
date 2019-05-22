main: evaluate_calculation.hpp libevaluate_calculation.so
	clang++ -std=c++17 -stdlib=libc++ -nodefaultlibs -L . -levaluate_calculation main.cc -o main
	chmod 555 main
libevaluate_calculation.so: evaluate_calculation.cc evaluate_calculation.hpp
	clang++ -std=c++17 -stdlib=libc++ -fPIC -Ofast -flto=full -shared -nodefaultlibs -lmath evaluate_calculation.cc -o libevaluate_calculation.so
	chmod 555 lib*
build_dlib: libevaluate_calculation.so
clean: main libevaluate_calculation.so
	rm main lib*
