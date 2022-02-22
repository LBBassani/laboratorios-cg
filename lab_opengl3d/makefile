all:
	g++ -o test.out -I ../Third-party-libs/glm/ -I ../Common/Domain opengl3d.cpp -lGL -lGLU -lglut

teste:
	g++ -o test.out -I ../Third-party-libs/glm/ -I ../Common/Domain opengl3d.cpp -lGL -lGLU -lglut -DTEST 

run: test.out
	./test.out

clean:
	rm *.out