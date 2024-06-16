#include "./GameFileStore.hpp"


auto GameFileStore::saveNewGame() -> void {

    auto lastGameId = std::string();
    auto lastGameIdFile = std::fstream(
            Path::NEXT_GAME_TO_SAVE_PATH,
            std::ios::in);
    lastGameIdFile >> lastGameId;
    lastGameIdFile.close();

    auto savedGameFileName = std::string(Path::GAME_SAVE_PATH);
    savedGameFileName += "/game_" + lastGameId + ".txt";

    auto savedGame = std::ofstream(savedGameFileName, std::ios::out | std::ios::trunc);

    auto lastMovePlayer = std::to_string(static_cast<int>(GameField::currentMovePlayer));
    savedGame << lastMovePlayer << "\n";
    savedGame << GameStatistic::stepsDone << "\n";
    savedGame << GameStatistic::allFiguresEaten << "\n";
    savedGame << GameStatistic::firstPlayerAte << "\n";
    savedGame << GameStatistic::secondPlayerAte << "\n";
    savedGame << GameStatistic::gameMode << "\n";

    auto stateLine = std::string();
    for (auto const &row: GameField::stateMatrix) {
        stateLine = "";
        for (auto const &field: row) {
            auto fieldVal = static_cast<int>(field);
            fieldVal = fieldVal == -1 ? 3 : fieldVal;
            stateLine += std::to_string(static_cast<int>(fieldVal));
        }
        savedGame << stateLine << "\n";
    }


    lastGameIdFile = std::fstream(
            Path::NEXT_GAME_TO_SAVE_PATH,
            std::ios::out | std::ios::trunc);
    lastGameIdFile << std::to_string(std::stoi(lastGameId) + 1);

}

auto GameFileStore::saveOldGame(const std::string &loadedGameNumber) -> void {

    auto path = std::filesystem::path(Path::GAME_SAVE_PATH);

    auto filename = std::string();
    auto gameNumber = std::string();

    for (auto const& entry : std::filesystem::directory_iterator(path)) {
        gameNumber = GameFileStore::getGameNumber(entry.path().string());
        if (gameNumber == loadedGameNumber) {
            filename = entry.path().string();
            break;
        };
    }

    auto loadedGameFile = std::fstream(filename, std::ios::out | std::ios::trunc);
    loadedGameFile << std::to_string(static_cast<int>(GameField::currentMovePlayer)) << "\n";
    loadedGameFile << GameStatistic::stepsDone << "\n";
    loadedGameFile << GameStatistic::allFiguresEaten << "\n";
    loadedGameFile << GameStatistic::firstPlayerAte << "\n";
    loadedGameFile << GameStatistic::secondPlayerAte << "\n";
    loadedGameFile << GameStatistic::gameMode << "\n";

    auto stateLine = std::string();
    for (auto const &row: GameField::stateMatrix) {
        stateLine = "";
        for (auto const &field: row) {
            auto fieldVal = static_cast<int>(field);
            fieldVal = fieldVal == -1 ? 3 : fieldVal;
            stateLine += std::to_string(static_cast<int>(fieldVal));
        }
        loadedGameFile << stateLine << "\n";
    }

    GameField::currentLoadedGame = "";

}

auto GameFileStore::uploadGame(std::string const& filename ) -> void {
    auto savedGameFile = std::fstream(filename, std::ios::in);
    auto lastMovePlayer = std::string();

    GameField::playerFigures.clear();
    GameField::playerFigures.resize(9);
    for (auto &figureRow : GameField::playerFigures)
        figureRow.resize(9);


//    savedGameFile >> lastMovePlayer;
    getline(savedGameFile, lastMovePlayer);

    auto doneSteps = std::string();
    auto figuresEaten = std::string();
    auto firstPlayerAte = std::string();
    auto secondPlayerAte = std::string();
    auto mode = std::string();

    getline(savedGameFile, doneSteps);
    getline(savedGameFile, figuresEaten);
    getline(savedGameFile, firstPlayerAte);
    getline(savedGameFile, secondPlayerAte);
    getline(savedGameFile, mode);

    GameStatistic::stepsDone = std::stoi(doneSteps);
    GameStatistic::allFiguresEaten = std::stoi(figuresEaten);
    GameStatistic::firstPlayerAte = std::stoi(firstPlayerAte);
    GameStatistic::secondPlayerAte = std::stoi(secondPlayerAte);
    GameStatistic::gameMode = std::to_string(static_cast<int>(GameMode::PLAYER_VS_PLAYER)) == mode ? GameMode::PLAYER_VS_PLAYER : GameMode::PLAYER_VS_COMPUTER;
    GameStatistic::printStatistic();
    auto playerOneFigures = 0;
    auto playerTwoFigures = 0;

    auto gameStateLine = std::string();
    auto state = std::string();
    auto lines = std::vector<std::string>();

    auto getStateValue = [](int state) -> FieldState {
        switch (state) {
            case 0:
                return FieldState::EMPTY;
            case 1:
                return FieldState::PLAYER_ONE;
            case 2:
                return FieldState::PLAYER_TWO;
            default:
                return FieldState::NOT_EXIST;
        }
    };

    while (getline(savedGameFile, gameStateLine)) lines.push_back(gameStateLine);

    for (auto row = 0; row < GameField::stateMatrix.size(); ++row) {
        for (auto col = 0; col < GameField::stateMatrix[row].size(); ++col) {
            state = lines[row][col];
            fmt::println("{}", state);
            if (state == "1") {
                auto figure = std::make_unique<PlayerFigure>(GameField::playerOne->getPlayerColor());
                GameLayoutBuilder::setPlayerFigurePosition(figure.get(), GameField::fieldMatrix[row][col]->getPosition());
                GameField::playerFigures[row][col] = std::move(figure);
                playerOneFigures++;
            } else if (state == "2") {
                auto figure = std::make_unique<PlayerFigure>(GameField::playerTwo->getPlayerColor());
                GameLayoutBuilder::setPlayerFigurePosition(figure.get(), GameField::fieldMatrix[row][col]->getPosition());
                GameField::playerFigures[row][col] = std::move(figure);
                playerTwoFigures++;
            }

            GameField::stateMatrix[row][col] = getStateValue(std::stoi(state));
        }
    }

    GameStatistic::spaceLeft = GameStatistic::spaceLeft - playerOneFigures - playerTwoFigures;

    GameField::freeSpaceLabel->setText("Free Space Left: " + std::to_string(GameStatistic::spaceLeft));
    mode = "Game mode: ";
    mode += GameStatistic::gameMode == GameMode::PLAYER_VS_PLAYER ? "PLAYER VS PLAYER" : "PLAYER VS COMPUTER";
    GameField::gameModeLabel->setText(mode);


    GameField::playerOneCountBar->setCountedItems(playerOneFigures);
    GameField::playerTwoCountBar->setCountedItems(playerTwoFigures);
    GameField::playerOne->setFieldCount(playerOneFigures);
    GameField::playerTwo->setFieldCount(playerTwoFigures);
    GameField::currentMovePlayer = std::stoi(lastMovePlayer) == 1 ? Player::FIRST : Player::SECOND;
    GameField::movePlayerLabel->setText(GameField::currentMovePlayer == Player::FIRST ? "Current player: 1" : "Current player: 2");
    GameField::movePlayerLabel->setColor(GameField::currentMovePlayer == Player::FIRST ? GameField::playerOne->getPlayerColor() : GameField::playerTwo->getPlayerColor());
    GameField::printFigureMatrix();
    GameField::printStateMatrix();
    GameStatistic::printStatistic();
    GameField::finishGame(false);

    auto loadedGame = GameFileStore::getGameNumber(filename);
    GameField::currentLoadedGame = loadedGame;
}

auto GameFileStore::getGameNumber(std::string const& filename) -> std::string {
    auto gameNumber = std::string();

    for (char ch : filename)
        if (ch >= '0' && ch <= '9') gameNumber += ch;

    return gameNumber;
}