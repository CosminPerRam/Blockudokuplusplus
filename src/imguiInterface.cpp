
#include "imguiInterface.h"

#include "settings.h"
#include "audio.h"
#include "game.h"
#include "utilities.h"

#include <SFML/Window/Event.hpp>

char ImguiInterface::fileName[64] = {"settings.cfg"};

void ImguiInterface::Custom::HelpMarker(const char* desc)
{
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

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

void ImguiInterface::update(sf::RenderWindow& window, sf::Time& dt) {
	ImGui::SFML::Update(window, dt);
}

void ImguiInterface::draw(sf::RenderWindow& window) {
	if (Settings::General::showImgui)
		return;

	ImGui::Begin("Settings");

	if (ImGui::Button("Hide"))
		Settings::General::showImgui = false;
	Custom::HelpMarker("Press 'M' to hide/show this menu.");
	ImGui::SameLine();
	//if (ImGui::Button("Save"))
	//	ImGui::OpenPopup("FileSavedPopup");
	//ImGui::SameLine();
	//if (ImGui::Button("Load"))
	//	ImGui::OpenPopup("FileLoadedPopup");

	if (ImGui::BeginPopup("FileSavedPopup")) {
		bool saved = Settings::save(fileName);
		ImGui::Text(saved ? "Successfully saved!" : "Couldn't save.");
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopup("FileLoadedPopup")) {
		bool loaded = Settings::load(fileName);

		ImGui::Text(loaded ? "Successfully loaded!" : "Couldn't load.");
		ImGui::EndPopup();
	}

	//ImGui::InputText("FileName", ImguiInterface::fileName, FILENAME_LENGTH);

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Gameplay"))
		{
			if (ImGui::TreeNode("Game"))
			{
				if (ImGui::Button("Restart game"))
					Game::restart();
				ImGui::SameLine();
				if (ImGui::Button("Clear board"))
					Game::theTable->reset();

				ImGui::Separator();

				if (ImGui::Checkbox("Autoplay", &Settings::Gameplay::autoplay)) {
					if (Settings::Gameplay::checkGameInAdvance)
						Settings::Gameplay::checkGameInAdvance = false;
				}
				Custom::HelpMarker("Let the game play itself.\nStops before game is lost.");
				if (Settings::Gameplay::autoplay) {
					ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);
					ImGui::SliderFloat("Delay seconds", &Settings::Gameplay::autoplayDelay, 0.2f, 2.f);
				}
				else {
					ImGui::SameLine();
					if (ImGui::Button("Bot place set"))
						Game::theBot.doSet();
					Custom::HelpMarker("Let the bot place the holding set of blocks.");
				}

				ImGui::Separator();
				if (ImGui::Checkbox("Check game in advance", &Settings::Gameplay::checkGameInAdvance))
				{
					if (Settings::Gameplay::autoplay)
						Settings::Gameplay::autoplay = false;

					if (Game::pickupBoard->isBoardLost())
						Game::theScore->setGameLost();
				}
				Custom::HelpMarker("Checks every possible move to\nverify if the game is lost.");

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Blocks"))
			{
				ImGui::Text("Type: ");
				ImGui::SameLine();
				if (ImGui::Button("Random")) {
					Settings::Gameplay::blockModel = -1;
					Game::pickupBoard->regenerateBlocks(pickupBlocks::existing);
				}
				ImGui::SameLine();
				if (ImGui::Button("Model"))
					ImGui::OpenPopup("ModelGeneratePopup");
				ImGui::SameLine();
				if (ImGui::Button("Custom"))
					ImGui::OpenPopup("CustomGeneratePopup");

				if (ImGui::BeginPopup("ModelGeneratePopup"))
				{
					for (size_t i = 0; i < structures::grouped.size(); i++) {
						if (ImGui::Selectable(structures::grouped[i]->name)) {
							Settings::Gameplay::blockModel = i;
							Game::pickupBoard->regenerateBlocks(pickupBlocks::existing);
						}
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopup("CustomGeneratePopup"))
				{
					Settings::Gameplay::blockModel = -2;

					static unsigned cbs_min = 1, cbs_cbsmax = 5;

					ImGui::PushItemWidth(68);
					if(ImGui::SliderScalar("Width", ImGuiDataType_U32, &Settings::Gameplay::customBlockSizeWidth, &cbs_min, &cbs_cbsmax, "%u"))
						Game::pickupBoard->regenerateBlocks(pickupBlocks::existing);
					if(ImGui::SliderScalar("Height", ImGuiDataType_U32, &Settings::Gameplay::customBlockSizeHeight, &cbs_min, &cbs_cbsmax, "%u"))
						Game::pickupBoard->regenerateBlocks(pickupBlocks::existing);
					ImGui::PopItemWidth();

					ImGui::Separator();

					for (unsigned i = 0; i < Settings::Gameplay::customBlockSizeHeight; i++) {
						for (unsigned j = 0; j < Settings::Gameplay::customBlockSizeWidth; j++) {
							if (j > 0)
								ImGui::SameLine();

							ImGui::PushID(i * 5 + j);
							if (ImGui::Selectable(" ", &Settings::Gameplay::customBlockStructure[i][j], ImGuiSelectableFlags_DontClosePopups, { 16, 16 }))
								Game::pickupBoard->regenerateBlocks(pickupBlocks::existing);
							ImGui::PopID();
						}
					}

					ImGui::Separator();

					ImGui::EndPopup();
				}

				ImGui::Text("Selected: ");
				ImGui::SameLine();
				if (Settings::Gameplay::blockModel == -1)
					ImGui::Text("Random");
				else if (Settings::Gameplay::blockModel == -2)
					ImGui::Text("Custom");
				else
					ImGui::Text(structures::grouped[Settings::Gameplay::blockModel]->name);

				ImGui::Separator();
				ImGui::Text("Regenerate: ");
				ImGui::SameLine();
				if (ImGui::Button("All"))
					Game::pickupBoard->regenerateBlocks(pickupBlocks::all);
				ImGui::SameLine();
				if (ImGui::Button("Missing"))
					Game::pickupBoard->regenerateBlocks(pickupBlocks::missing);

				ImGui::Separator();
				ImGui::Checkbox("Continously generation", &Settings::Gameplay::continousGenerate);
				Custom::HelpMarker("Never lets a slot to be empty\n(if it was occupied beforehand)!");

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Score"))
			{
				int APM = 20;
				int SPM = 40;

				/*ImGui::Text("APM:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(APM).c_str());
				Custom::HelpMarker("Actions per minute.");
				ImGui::SameLine();
				ImGui::Text("SPM:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(SPM).c_str());
				Custom::HelpMarker("Score per minute.");*/

				ImGui::Text("Current: ");
				ImGui::SameLine();
				ImGui::Text(std::to_string(Game::theScore->score).c_str());
				ImGui::SameLine();
				ImGui::Text("Highscore: ");
				ImGui::SameLine();
				ImGui::Text(std::to_string(Score::Data::getLocalBest()).c_str());

				if (ImGui::Button("Reset score"))
					Game::theScore->reset();
				ImGui::SameLine();
				if (ImGui::Button("Reset highscore"))
					Score::Data::writeLocalBest(0);

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Aspect/Audio"))
		{
			//ImGui::Checkbox("Animations", &Settings::Aspect::animations);
			//let change font

			if (ImGui::TreeNode("Colors"))
			{
				if (ImGui::Button("Set default values")) {
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
			if (ImGui::TreeNode("Audio")) {
				ImGui::Checkbox("Mute", &Settings::Audio::muted);
				if (!Settings::Audio::muted)
					ImGui::SliderInt("Volume", &Settings::Audio::volume, 0, 100);

				ImGui::SliderFloat("Pitch", &Settings::Audio::pitch, 0.1f, 1.9f);

				Audio::updateState();

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();

	ImGui::SFML::Render(window);
}
