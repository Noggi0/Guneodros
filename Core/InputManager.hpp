#include "./EntityManager.hpp"

// #if WIN32
//     #include <windows.h>
// #endif

class InputManager {
    public:
        InputManager() {
        };
        void update() {
            // for (int i = 0; i < 256; i++) {
            //     this->key_state[i] = (GetAsyncKeyState(i) & 0x8000) ? 1 : 0;
            // }
        }
        bool isKeyPressed(int x) {
            return key_state[x];
        }
        ~InputManager() {

        };
    private:
        bool key_state[256] = {};
};