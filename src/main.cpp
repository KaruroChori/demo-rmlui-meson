#define RMLUI_SDL_VERSION_MAJOR 3
#include "subprojects/rmlui/Backends/RmlUi_Backend.h"
#include <RmlUi/Core.h>
#include "Shell.h"
#include "subprojects/rmlui/Backends/RmlUi_Platform_SDL.h"
#include "subprojects/rmlui/Backends/RmlUi_Renderer_SDL.h"

class MyRenderInterface : public Rml::RenderInterface
{
    // RmlUi sends vertices, indices and draw commands through this interface for your
    // application to render how you'd like.
    /* ... */
};

struct ApplicationData {
    bool show_text = true;
    Rml::String animal = "dog";
} my_data;

int main(int argc, char** argv){
    // Constructs the system and render interfaces, creates a window, and attaches
    // the renderer.
    if (not Backend::Initialize("Demo UI", 1280, 720, true)) {
        return -1;
    }

    Rml::SetSystemInterface(Backend::GetSystemInterface());
    Rml::SetRenderInterface(Backend::GetRenderInterface());

    Rml::Initialise();

    // Create a context to display documents within.
    Rml::Context *context = Rml::CreateContext("main", Rml::Vector2i(1280, 720));

    if(!Rml::LoadFontFace("./font/LatoLatin-Regular.ttf"))throw "Cannot load font";
    if(!Rml::LoadFontFace("./font/NotoEmoji-Regular.ttf", true))throw "Cannot load font";

    // Set up data bindings to synchronize application data.
    if (Rml::DataModelConstructor constructor = context->CreateDataModel("animals")) {
        constructor.Bind("show_text", &my_data.show_text);
        constructor.Bind("animal", &my_data.animal);
    }
    
    // Now we are ready to load our document.
    Rml::ElementDocument *document =
        context->LoadDocument("./res/hello_world.rml");
    document->Show();

    // Replace and style some text in the loaded document.
    Rml::Element *element = document->GetElementById("world");
    if(element){
        element->SetInnerRML(reinterpret_cast<char const *>(u8"🌍"));
        element->SetProperty("font-size", "1.5em");
    }

    bool running = true; 
    while (running) {
        // Handle input and window events. 
        running = Backend::ProcessEvents(context, &Shell::ProcessKeyDownShortcuts, true); 
    
        // This is a good place to update your game or application. 
    
        // Always update the context before rendering. 
        context->Update(); 
    
        // Prepare the backend for taking rendering commands from RmlUi and then render the context. 
        Backend::BeginFrame(); 
        context->Render(); 
        Backend::PresentFrame(); 
    }

    Rml::Shutdown();
}