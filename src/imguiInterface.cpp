
#include "imguiInterface.h"

#include "imguiInterface.h"

#include "settings.h"
#include "audio.h"
#include "game.h"
#include "utilities.h"

#include <SFML/Window/Event.hpp>

char ImguiInterface::fileName[64] = {"settings.cfg"};
ImGuiWindowFlags ImguiInterface::window_flags = 0;
ImGuiStyle* ImguiInterface::style = nullptr;
sf::Time ImguiInterface::lastTime = sf::Time::Zero, ImguiInterface::lastUpdateTime = sf::Time::Zero;
ImguiInterface::Data ImguiInterface::data;

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

void ImguiInterface::Data::update() {
	data.historyFps.push_back(static_cast<float>(Game::fetchFps()));
	if (data.historyFps.size() > 64)
		data.historyFps.erase(data.historyFps.begin());

	data.averageFps = 0;
	unsigned historyFpsAmount = data.historyFps.size();
	for (unsigned i = 0; i < historyFpsAmount; i++)
		data.averageFps += static_cast<unsigned>(data.historyFps[i]);
	data.averageFps /= historyFpsAmount;
}

void ImguiInterface::initialize(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
	style = &ImGui::GetStyle();
	style->WindowRounding = 4.f;
	style->WindowTitleAlign.x = 0.5f;
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
	sf::Time updateTime = dt - lastTime;
	ImGui::SFML::Update(window, updateTime);

	lastUpdateTime += updateTime;
	if (lastUpdateTime.asSeconds() * 1000 > 1000 / IMGUI_REFRESHRATE)
	{
		ImguiInterface::Data::update();
		lastUpdateTime = sf::Time::Zero;
	}

	lastTime = dt;
}

void ImguiInterface::draw(sf::RenderWindow& window) {
	if (!Settings::General::showImgui) {
		ImGui::SFML::Render(window);
		return;
	}

	ImGui::Begin("Settings", &Settings::General::showImgui, window_flags);

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
	ImGui::Text("Press 'M' to hide/show this menu.");
	if (ImGui::BeginTabBar("TabBar"))
	{
		if (ImGui::BeginTabItem("Gameplay"))
		{
			if (ImGui::TreeNode("Table"))
			{
				if (ImGui::Button("Restart"))
					Game::restart();
				ImGui::SameLine();
				if (ImGui::Button("Clear"))
					Game::theTable->reset();

				ImGui::Separator();

				if (ImGui::Checkbox("Autoplay", &Settings::Gameplay::autoplay)) {
					if (Settings::Gameplay::checkGameInAdvance)
						Settings::Gameplay::checkGameInAdvance = false;
				}
				Custom::HelpMarker("Let the game play itself.\nStops before game is lost.");

				if (Settings::Gameplay::autoplay)
					ImGui::SliderFloat("Delay", &Settings::Gameplay::autoplayDelay, 0.2f, 4.f, "%.3f seconds");
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

			if (ImGui::TreeNode("Pickup board"))
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
				ImGui::Text("Time played:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(Game::theScore->timePlayedSeconds).c_str());
				ImGui::SameLine();
				ImGui::Text("seconds.");

				ImGui::Text("APM:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(Game::theScore->apm).c_str());
				Custom::HelpMarker("Actions per minute.");
				ImGui::SameLine();
				ImGui::Text("SPM:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(Game::theScore->spm).c_str());
				Custom::HelpMarker("Score per minute.");

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
			if (ImGui::TreeNode("Window"))
			{
				ImGui::PlotLines("##frpsPlot", &data.historyFps[0], data.historyFps.size());
				Custom::HelpMarker("Frames Per Second");

				ImGui::Text("Fps:");
				ImGui::SameLine();
				ImGui::Text(std::to_string((unsigned)data.historyFps.back()).c_str());
				ImGui::SameLine();
				ImGui::Text("Avg:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(data.averageFps).c_str());
				ImGui::SameLine();
				if (ImGui::Checkbox("Vsync", &Settings::General::vsync))
					Game::updateVsyncSetting();
				Custom::HelpMarker("Limits the refresh rate to\nyour monitor's one.");

				ImGui::Text("Frame time:");
				ImGui::SameLine();
				ImGui::Text(std::to_string(Game::fetchFrametime()).c_str());
				ImGui::SameLine();
				ImGui::Text("ms ");

				static const char* aalevelsNames[] = { "None", "x2", "x4", "x8", "x16" };
				const char* aalevelName = aalevelsNames[Settings::General::aalevel];
				ImGui::PushItemWidth(64);
				if (ImGui::BeginCombo("Antialiasing", aalevelName)) {
					for (unsigned i = 0; i < 5; i++) {
						const bool selected = (Settings::General::aalevel == i);
						if (ImGui::Selectable(aalevelsNames[i], selected)) {
							Settings::General::aalevel = i;
							Game::updateAntialiasingSetting();
						}

						if (selected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}
				ImGui::PopItemWidth();
				Custom::HelpMarker("Changing the antialiasing level\nreinitializes the window.");

				ImGui::TreePop();
			}
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
				{
					ImGui::SameLine();
					ImGui::PushItemWidth(120);
					ImGui::SliderInt("Volume", &Settings::Audio::volume, 0, 100);
					ImGui::PopItemWidth();
				}

				ImGui::PushItemWidth(179);
				ImGui::SliderFloat("Pitch", &Settings::Audio::pitch, 0.1f, 1.9f);
				ImGui::PopItemWidth();

				Audio::updateState();

				ImGui::TreePop();
			}
			if (ImGui::TreeNode("ImGui"))
			{
				ImGui::PushItemWidth(77);
				ImGui::Text("Theme:");
				ImGui::SameLine();
				ImGui::ShowStyleSelector("##StyleSelector");
				ImGui::PopItemWidth();
				ImGui::SameLine();
				if (ImGui::Button("Toggle background"))
					window_flags ^= ImGuiWindowFlags_NoBackground;

				ImGui::Separator();

				if (ImGui::Button("Style editor"))
					ImGui::OpenPopup("StyleEditor");
				Custom::HelpMarker("Opens ImGui's integrated style editor.");

				if (ImGui::BeginPopup("StyleEditor"))
				{
					ImGui::ShowStyleEditor(style);

					ImGui::EndPopup();
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();

	ImGui::SFML::Render(window);
}
