CXX = g++
PROJSETTINGS = -std=c++17 -I./lib/include -L./lib/lib -lglew32 -lglfw3 -lopengl32 -lWs2_32 -lole32 -lcomctl32 -lgdi32 -lcomdlg32 -luuid
MAINFILE = rendererTest
OBJFILES = DebugRenderer.o BitmapLoader.o Camera.o FrameBuffer.o GraphicsObject2D.o HSVxRGBconversion.o IBO.o Mat4.o Material.o Mesh.o PostEffect.o Renderer2D.o Shader.o Texture.o VAO.o VBO.o Vec2.o Vec3.o Vec4.o Window.o Light.o

compile: main.o $(OBJFILES)
	$(CXX) $(MAINFILE).o $(OBJFILES) -o output $(PROJSETTINGS)

Light.o: Light.cpp
	$(CXX) -c Light.cpp $(PROJSETTINGS)

main.o: $(MAINFILE).cpp
	$(CXX) -c $(MAINFILE).cpp $(PROJSETTINGS)

BitmapLoader.o: BitmapLoader.cpp
	$(CXX) -c BitmapLoader.cpp $(PROJSETTINGS)

Camera.o: Camera.cpp
	$(CXX) -c Camera.cpp $(PROJSETTINGS)

FrameBuffer.o: FrameBuffer.cpp
	$(CXX) -c FrameBuffer.cpp $(PROJSETTINGS)

GraphicsObject2D.o: GraphicsObject2D.cpp
	$(CXX) -c GraphicsObject2D.cpp $(PROJSETTINGS)

HSVxRGBconversion.o: HSVxRGBconversion.cpp
	$(CXX) -c HSVxRGBconversion.cpp $(PROJSETTINGS)

IBO.o: IBO.cpp
	$(CXX) -c IBO.cpp $(PROJSETTINGS)

Mat4.o: Mat4.cpp
	$(CXX) -c Mat4.cpp $(PROJSETTINGS)

Material.o: Material.cpp
	$(CXX) -c Material.cpp $(PROJSETTINGS)

Mesh.o: Mesh.cpp
	$(CXX) -c Mesh.cpp $(PROJSETTINGS)

PostEffect.o: PostEffect.cpp
	$(CXX) -c PostEffect.cpp $(PROJSETTINGS)

Renderer2D.o: Renderer2D.cpp
	$(CXX) -c Renderer2D.cpp $(PROJSETTINGS)

Shader.o: Shader.cpp
	$(CXX) -c Shader.cpp $(PROJSETTINGS)

Texture.o: Texture.cpp
	$(CXX) -c Texture.cpp $(PROJSETTINGS)

VAO.o: VAO.cpp
	$(CXX) -c VAO.cpp $(PROJSETTINGS)

VBO.o: VBO.cpp
	$(CXX) -c VBO.cpp $(PROJSETTINGS)

Vec2.o: Vec2.cpp
	$(CXX) -c Vec2.cpp $(PROJSETTINGS)

Vec3.o: Vec3.cpp
	$(CXX) -c Vec3.cpp $(PROJSETTINGS)

Vec4.o: Vec4.cpp
	$(CXX) -c Vec4.cpp $(PROJSETTINGS)

Window.o: Window.cpp
	$(CXX) -c Window.cpp $(PROJSETTINGS)

DebugRenderer.o: DebugRenderer.cpp
	$(CXX) -c DebugRenderer.cpp $(PROJSETTINGS)

run:
	output $(ARGS)

clean:
	del *.o output
