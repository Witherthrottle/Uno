# UNO Game Simulation in C++  

This repository contains a **UNO Game Simulation** implemented in C++. The game includes features for managing cards, player actions, and customizable game options.  

## Features  
1. **Special Card Support**:  
   - Reverse (`Rev`), Skip (`S`), Draw Two (`D2`), Wild (`W`), and Draw Four (`D-4`) cards.  
   - Implemented special behaviors for each card type.  
2. **Customizable Gameplay**:  
   - Players can set the number of players (1-4) and the number of starting cards (1-9).  
   - A special game mode where only special cards are drawn can be enabled.  
3. **Themes**:  
   - Support for different themes with pre-set options such as Blue, Green, Aqua, etc.  
4. **Player Turn Management**:  
   - A circular turn system implemented using a `CircularVector` template.  
5. **Error Handling**:  
   - Invalid inputs are managed with a custom exception class `Invalidinput`.  

---

## Classes Overview  

### 1. `Menu`  
Handles user interactions such as setting themes, the number of players, starting cards, and enabling/disabling special game modes.  

### 2. `CircularVector<T>`  
Manages the turn system for players. Includes functionalities like reversing the order of turns and moving to the next turn.  

### 3. `Card` (Base Class)  
Defines a generic interface for all card types.  

### 4. Derived Card Classes  
- **`NormalCard`**: Represents standard UNO cards (e.g., `R-9` for Red 9).  
- **`Draw2Card`**: Represents the `Draw 2` cards (e.g., `D2-B` for Draw 2 Blue).  
- **`SkipCard`**: Represents `Skip` cards (e.g., `S-R` for Skip Red).  
- **`ReverseCard`**: Represents `Reverse` cards (e.g., `Rev-Y` for Reverse Yellow).  
- **`Draw4Card`**: Represents `Draw 4` wild cards.  
- **`WildCard`**: Represents wild cards that allow changing the active color.  

### 5. `Deck`  
Handles the initialization of the deck, card drawing, and shuffling. The deck can be initialized with either normal or special-only cards.  

### 6. `Player`  
Represents individual players, manages their cards, and interacts with the shared deck.  

---

## Installation and Usage  

1. **Clone the Repository**:  
   ```bash  
   git clone https://github.com/your-username/uno-game-simulation.git  
   cd uno-game-simulation  
   ```  

2. **Compile the Code**:  
   Use any C++ compiler such as GCC or MSVC. For GCC:  
   ```bash  
   g++ main.cpp -o uno_game  
   ```  

3. **Run the Program**:  
   ```bash  
   ./uno_game  
   ```  

---

## Gameplay Instructions  

1. The program starts with the main menu:  
   - Select "Play" to start the game.  
   - Select "Options" to customize game settings (e.g., themes, number of players).  

2. During gameplay:  
   - Players take turns drawing and playing cards.  
   - Special cards affect the flow of the game based on their behaviors.  

3. The game continues until one player has no cards left or another end condition is met.  

---

## Code Highlights  

1. **Dynamic Deck Generation**:  
   Cards are dynamically created and stored in a vector of pairs, combining card logic with ASCII art for easy display.  

2. **Special Card Effects**:  
   Special behaviors like drawing extra cards or skipping turns are managed with virtual functions overridden in derived classes.  

3. **Error Handling**:  
   User inputs are validated using the `Invalidinput` exception class, ensuring robust input handling.  

---

## Future Improvements  

1. Add multiplayer functionality (e.g., over LAN or internet).  
2. Enhance AI for single-player mode.  
3. Improve graphics with a GUI library (e.g., SDL, SFML).  
4. Add more detailed card animations.  

---

## Contribution  
Feel free to fork the repository and submit pull requests for improvements or bug fixes.  

---

## License  
This project is licensed under the MIT License. See the `LICENSE` file for details.  

---

## Acknowledgements  
- The ASCII art for cards was manually created to provide a visual experience in the console.  
- Special thanks to the UNO game for inspiration.  

---

Enjoy playing and coding! 🎮
