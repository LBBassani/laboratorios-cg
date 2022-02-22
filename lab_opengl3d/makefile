all:
	g++ -o test.out -I ../Third-party-libs/glm/ -I ../Common/Domain opengl3d.cpp -lGL -lGLU -lglut

teste:
	g++ -o test.out -I ../Third-party-libs/glm/ -I ../Common/Domain opengl3d.cpp -lGL -lGLU -lglut -DTEST

cube:
	g++ -o test.out -I ../Third-party-libs/glm/ -I ../Common/Domain opengl3d.cpp -lGL -lGLU -lglut -DCUBE

sphere:
	g++ -o test.out -I ../Third-party-libs/glm/ -I ../Common/Domain opengl3d.cpp -lGL -lGLU -lglut -DSPHERE

run: test.out
	./test.out

clean:
	rm *.out