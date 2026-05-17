#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class IAMenuPopup : public FLAlertLayer {
protected:
    CCTextInputNode* m_inputNode;

    bool init() override {
        if (!FLAlertLayer::init(150)) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        // Crear el fondo del menú
        auto bg = CCScale9Sprite::create("GJ_square01.png");
        bg->setContentSize({ 340.f, 220.f });
        bg->setPosition(winSize / 2);
        m_mainLayer->addChild(bg);

        // Título
        auto title = CCLabelBMFont::create("Asistente de IA", "goldFont.fnt");
        title->setPosition(winSize.width / 2, winSize.height / 2 + 85.f);
        title->setScale(0.8f);
        m_mainLayer->addChild(title);

        // Campo de texto para escribir la orden
        auto inputBg = CCScale9Sprite::create("square02b_001.png");
        inputBg->setContentSize({ 280.f, 40.f });
        inputBg->setPosition(winSize / 2);
        inputBg->setColor({ 0, 0, 0 });
        inputBg->setOpacity(100);
        m_mainLayer->addChild(inputBg);

        m_inputNode = CCTextInputNode::create(270.f, 30.f, "Escribe lo que quieres que haga la IA...", "bigFont.fnt");
        m_inputNode->setPosition(winSize / 2);
        m_inputNode->setAllowedChars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
        m_mainLayer->addChild(m_inputNode);

        // Menú para los botones
        auto menu = CCMenu::create();
        menu->setPosition({ 0, 0 });
        m_mainLayer->addChild(menu);

        // Botón de cerrar
        auto closeBtnSprite = ButtonSprite::create("X", "goldFont.fnt", "GJ_button_01.png", .6f);
        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeBtnSprite, this, menu_selector(IAMenuPopup::onClose)
        );
        closeBtn->setPosition(winSize.width / 2 - 150.f, winSize.height / 2 + 90.f);
        menu->addChild(closeBtn);

        // Botón de "Generar"
        auto generateBtnSprite = ButtonSprite::create("Generar", "goldFont.fnt", "GJ_button_01.png", .8f);
        auto generateBtn = CCMenuItemSpriteExtra::create(
            generateBtnSprite, this, menu_selector(IAMenuPopup::onGenerate)
        );
        generateBtn->setPosition(winSize.width / 2, winSize.height / 2 - 70.f);
        menu->addChild(generateBtn);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);

        return true;
    }

    void onClose(CCObject* sender) {
        this->removeFromParentAndCleanup(true);
    }

    // AQUÍ ES DONDE SE APLICA EL CÓDIGO PARA CREAR OBJETOS
    void onGenerate(CCObject* sender) {
        std::string prompt = m_inputNode->getString();
        
        if (prompt.empty()) {
            FLAlertLayer::create("Error", "¡No puedes dejar el campo vacío!", "OK")->show();
            return;
        }

        // 1. Conseguir la capa del editor que está abierta actualmente en el juego
        auto editorLayer = LevelEditorLayer::get();

        if (editorLayer) {
            // 2. Obtener el centro de la pantalla actual del editor para saber dónde poner el objeto
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            CCPoint posicionCentro = editorLayer->m_objectLayer->convertToNodeSpace(winSize / 2);

            // 3. Crear el objeto real usando el ID del juego (ID 8 es la espina/spike común)
            // Parámetros: createObject(ID_DEL_OBJETO, POSICIÓN_CCPOINT, HACER_UNDOABLE)
            auto nuevoObjeto = editorLayer->createObject(8, posicionCentro, true);

            if (nuevoObjeto) {
                // 4. Añadirlo visualmente al nivel y registrarlo en el historial para poder borrarlo con "Undo"
                editorLayer->m_editorUI->m_selectedObjects->addObject(nuevoObjeto);
                
                // Cerrar la interfaz de la IA para ver el objeto creado
                this->onClose(nullptr);
                return;
            }
        }

        // Si por alguna razón falla o no encuentra el editor
        FLAlertLayer::create("Error", "No se pudo crear el objeto en el editor.", "OK")->show();
    }

public:
    static IAMenuPopup* create() {
        auto ret = new IAMenuPopup();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};
