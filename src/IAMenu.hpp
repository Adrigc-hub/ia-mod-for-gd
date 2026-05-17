#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Definimos nuestra propia capa flotante (Popup)
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

        // Menú para los botones (Cerrar y Generar)
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

        // Habilitar clics en esta capa
        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);

        return true;
    }

    void onClose(CCObject* sender) {
        this->removeFromParentAndCleanup(true);
    }

    void onGenerate(CCObject* sender) {
        std::string prompt = m_inputNode->getString();
        
        if (prompt.empty()) {
            FLAlertLayer::create("Error", "¡No puedes dejar el campo vacío!", "OK")->show();
            return;
        }

        // Aquí se conectaría la lógica o la API de la IA.
        // Por ahora, muestra un aviso de que recibió la orden.
        std::string mensaje = "La IA está procesando: \"" + prompt + "\"\n(Aquí se ejecutará la creación de objetos).";
        FLAlertLayer::create("IA Procesando", mensaje.c_str(), "Genial")->show();
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
