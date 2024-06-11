#include "./GameFileStore.hpp"


auto GameFileStore::saveNewGame() -> void {

    auto lastGameId = std::string();
    auto lastGameIdFile = std::fstream(
            "/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/saved_game_data/next_save_game.txt",
            std::ios::in);
    lastGameIdFile >> lastGameId;
    lastGameIdFile.close();

    auto savedGameFileName = std::string(
            "/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/saved_game_data/game_");
    savedGameFileName += lastGameId + ".txt";

    auto savedGame = std::ofstream(savedGameFileName, std::ios::out | std::ios::trunc);

    auto lastMovePlayer = std::to_string(static_cast<int>(GameField::currentMovePlayer));
    savedGame << lastMovePlayer << "\n";

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
            "/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/saved_game_data/next_save_game.txt",
            std::ios::out | std::ios::trunc);
    lastGameIdFile << std::to_string(std::stoi(lastGameId) + 1);

}

auto GameFileStore::saveOldGame(const std::string &loadedGameNumber) -> void {

    auto path = std::filesystem::path("/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/saved_game_data");

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
    fmt::println("{}", std::filesystem::exists(filename));
    auto savedGameFile = std::fstream(filename, std::ios::in);
    auto lastMovePlayer = std::string();

    GameField::playerFigures.clear();
    GameField::playerFigures.resize(9);
    for (auto &figureRow : GameField::playerFigures)
        figureRow.resize(9);

    getline(savedGameFile, lastMovePlayer);

    auto playerOneFigures = 0;
    auto playerTwoFigures = 0;

    auto gameStateLine = std::string();
    auto state = std::string();
    auto lines = std::vector<std::string>();

    auto getStateValue = [](int state) -> FieldState {
        fmt::println("state ---> {}", state);
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

    GameField::playerOneCountBar->setCountedItems(playerOneFigures);
    GameField::playerTwoCountBar->setCountedItems(playerTwoFigures);
    GameField::playerOne->setFieldCount(playerOneFigures);
    GameField::playerTwo->setFieldCount(playerTwoFigures);
    GameField::currentMovePlayer = std::stoi(lastMovePlayer) == 1 ? CurrentMovePlayer::FIRST : CurrentMovePlayer::SECOND;
    GameField::movePlayerLabel->setText(GameField::currentMovePlayer == CurrentMovePlayer::FIRST ? "Current player: 1" : "Current player: 2");
    GameField::movePlayerLabel->setColor(GameField::currentMovePlayer == CurrentMovePlayer::FIRST ? GameField::playerOne->getPlayerColor() : GameField::playerTwo->getPlayerColor());
    GameField::printFigureMatrix();
    GameField::printStateMatrix();

    auto loadedGame = GameFileStore::getGameNumber(filename);
    GameField::currentLoadedGame = loadedGame;
}

auto GameFileStore::getGameNumber(std::string const& filename) -> std::string {
    auto gameNumber = std::string();

    for (char ch : filename)
        if (ch >= '0' && ch <= '9') gameNumber += ch;

    return gameNumber;
}