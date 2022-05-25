
#include "imguiInterface.h"

#include "settings.h"
#include "audio.h"
#include "game.h"

#include <SFML/Window/Event.hpp>

char ImguiInterface::fileName[64] = {"settings.cfg"};

void ImguiInterface::initialize(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
}

void ImguiInterface::shutdown() {
	ImGui::SFML::Shutdown();
}

void ImguiInterface::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	ImGui::SFML::ProcessEvent(theEvent);

	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::M)
		Settings::General::showImgui = !Settings::General::showImgui;
}

void ImguiInterface::update(sf::RenderWindow& window, sf::Time dt) {
	ImGui::SFML::Update(window, dt);
}

void ImguiInterface::draw(sf::RenderWindow& window) {
	if (Settings::General::showImgui) {
		ImGui::Begin("Settings");

		if (ImGui::Button("Hide"))
			Settings::General::showImgui = false;
		ImGui::SameLine();
		if (ImGui::Button("Save"))
			ImGui::OpenPopup("FileSavedPopup");
		if (ImGui::BeginPopup("FileSavedPopup")) {
			bool saved = Settings::save(fileName);
			ImGui::Text(saved ? "Successfully saved!" : "Couldn't save.");
			ImGui::EndPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Load"))
			ImGui::OpenPopup("FileLoadedPopup");
		if (ImGui::BeginPopup("FileLoadedPopup")) {
			bool loaded = Settings::load(fileName);

			ImGui::Text(loaded ? "Successfully loaded!" : "Couldn't load.");
			ImGui::EndPopup();
		}

		ImGui::InputText("FileName", ImguiInterface::fileName, FILENAME_LENGTH);

        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Gameplay"))
            {
				if (ImGui::TreeNode("Bot"))
				{
					ImGui::Checkbox("Autoplace", &Settings::Gameplay::autoplace);
					if (Settings::Gameplay::autoplace)
						ImGui::SliderFloat("Delay seconds", &Settings::Gameplay::autoplaceDelay, 0.25, 2);

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Blocks"))
				{
					ImGui::Text("Generate: ");
					ImGui::Checkbox("Continously", &Settings::Gameplay::continousGenerate);

					ImGui::Text("Type: ");
					ImGui::SameLine();
					if (ImGui::Button("Random"))
						Settings::Gameplay::blockModel = -1;
					ImGui::SameLine();
					if (ImGui::Button("Model"))
						ImGui::OpenPopup("ModelGeneratePopup");

					ImGui::Text("Selected: ");
					ImGui::SameLine();
					ImGui::Text(Settings::Gameplay::blockModel == -1 ? "Random" : structures::grouped[Settings::Gameplay::blockModel]->name);

					if (ImGui::Button("Regenerate"))
						Game::pickupBoard->generateBlocks(Settings::Gameplay::blockModel);

					if (ImGui::BeginPopup("ModelGeneratePopup"))
					{
						for (size_t i = 0; i < structures::grouped.size(); i++) {
							if (ImGui::Selectable(structures::grouped[i]->name))
								Settings::Gameplay::blockModel = i; //not really true mapping, if the structure array changes the name array needs to be changed too
						}

						ImGui::EndPopup();
					}

					ImGui::TreePop();
				}

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Aspect"))
            {
				ImGui::Checkbox("Animations", &Settings::Aspect::animations);

				if (ImGui::TreeNode("Colors"))
				{
					if (ImGui::Button("Reset")) {
						Settings::Aspect::defaultValues();

						Game::theTable->updateColors();
						Game::theScore->updateColors();
						Game::pickupBoard->updateColors();
					}

					if (ImGui::CollapsingHeader("General")) {
						ImGui::ColorEdit3("Background", Settings::Aspect::appBackground);
						ImGui::ColorEdit3("Pickup margins", Settings::Aspect::pickupMargins);
						ImGui::ColorEdit3("Text", Settings::Aspect::textColor);

						Game::theScore->updateColors();
						Game::pickupBoard->updateColors();
					}
					if (ImGui::CollapsingHeader("Cells")) {
						ImGui::ColorEdit3("Solid", Settings::Aspect::cellSolid);
						ImGui::ColorEdit3("Preview", Settings::Aspect::cellPreview);
						ImGui::ColorEdit3("Completion", Settings::Aspect::cellCompletion);
						ImGui::ColorEdit3("Margins", Settings::Aspect::cellMargins);

						Game::theTable->updateColors();
					}
					if (ImGui::CollapsingHeader("Table")) {
						ImGui::ColorEdit3("Odd", Settings::Aspect::tableOdd);
						ImGui::ColorEdit3("Even", Settings::Aspect::tableEven);
						ImGui::ColorEdit3("Minor lines", Settings::Aspect::tableMinor);
						ImGui::ColorEdit3("Major lines", Settings::Aspect::tableMajor);

						Game::theTable->updateColors();
					}

					ImGui::TreePop();
				}

                ImGui::EndTabItem();
            }
			if (ImGui::BeginTabItem("Audio"))
			{
				ImGui::Checkbox("Mute", &Settings::Audio::muted);
				if (!Settings::Audio::muted)
					ImGui::SliderInt("Volume", &Settings::Audio::volume, 0, 100);

				ImGui::SliderFloat("Pitch", &Settings::Audio::pitch, 0.1f, 1.9f);

				Audio::updateState();

				ImGui::EndTabItem();
			}
            ImGui::EndTabBar();
        }
		ImGui::End();
	}

	ImGui::SFML::Render(window);
}