#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include "IAMenu.hpp"

using namespace geode::prelude;

// Modificamos la capa del Editor de Niveles
class $modify(MyEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* level, bool p1) {
        if (!LevelEditorLayer::init(level, p1)) return false;

        // Buscamos el menú lateral derecho donde suelen ir los botones de configuración/herramientas
        auto editorMenu = this->getChildByID("settings-menu");
        
        if (!editorMenu) {
            // Si no se encuentra por ID, lo buscamos en el menú principal del editor
            editorMenu = this->getChildByID("main-menu");
        }

        if (editorMenu) {
            // Crear el botón con el texto "IA"
            auto iaBtnSprite = ButtonSprite::create("IA", "goldFont.fnt", "GJ_button_04.png", .7f);
            
            auto iaBtn = CCMenuItemSpriteExtra::create(
                iaBtnSprite,
                this,
                menu_selector(MyEditorLayer::onIAButtonClick)
            );

            // Asignar un ID único para evitar conflictos con otros mods
            iaBtn->setID("ia-helper-button"_spr);

            // Añadir el botón al menú del editor y actualizar la posición de los elementos
            editorMenu->addChild(iaBtn);
            editorMenu->updateLayout();
        }

        return true;
    }

    // Función que se ejecuta al presionar el botón "IA"
    void onIAButtonClick(CCObject* sender) {
        auto popup = IAMenuPopup::create();
        if (popup) {
            popup->show();
        }
    }
};
