default:
	gcc main.c -o test -I ./ -I ./raylib/ -L E:/raylib-5.5/src -lraylib -lopengl32 -lgdi32 -lwinmm