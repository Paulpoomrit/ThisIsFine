# Game Design Document

> 💡 The project is currently being incrementally updated from its original version submitted for Grow Up! Game Jam in August.

**Game Title**: This is Fine

**Game Platform**: Web, IOS, Android, PC, Mac

**Genre**: clicker game, rogue-like

**Target Age**: Everyone

**Game-Summary**:  Fight ever-growing fires each fire season and last as long as you can!

**Similar Pieces/ Inspiration**:

- cookie clicker

---

## Project Architecture

<img width="1169" height="901" alt="image" src="https://github.com/user-attachments/assets/97eb0621-c592-424d-bcf6-df88d210e0dd" />

At the beginning, the main calls `MainMenu::DoMainMenu`, a static function that initializes the MainMenu widget and returns only after the player selects one of the three possible cases: quit, start in infinite mode, or start in story mode.

The current `DoLevel` is called after `DoMainMenu`; however, it is meant to be called after `DoConfigScreen` (to be implemented), where the player selects and buys their tools.

Similar to the `DoMainMenu`, the `DoLevel` is a static member function of the `LevelManager` class that handles all level-related tasks, including initializing the graphics scenes, items, and their logic components (more on that below). The function returns a std::variant of structs (Win or Lose) only if it determines that the endgame condition has been met.

Once the Win or Lose struct is return, we either loop back to the config screen or, if they lose, show the `EndScreen` (to be implemented), Then send the player back to the main menu.

`StoryMode` is currently being greyed out for flexibility at this point, but it should utilize both the `DoConfigScreen` and `DoLevel` with more utility classes to display and keep track of stories and some visuals.

---

## Widget + Graphics Hierarchy

<img width="741" height="747" alt="image 1" src="https://github.com/user-attachments/assets/3f068d44-c18d-4a82-9f77-b91c01e9e4ce" /> <img width="1305" height="824" alt="image 2" src="https://github.com/user-attachments/assets/1ad41057-4681-4688-b54c-27284cdb3bbb" />

Since QT wraps around OpenGL, here is a quick reminder of how the layers of classes are composed. GameWindow is your typical Qt widget, which contains the `graphicsView`, another widget that acts as a sort of “window” to the OpenGL scene (could be the entire scene or just a portion of it). The GameScene itself could be thought of as the **Scene Graph** from OpenGL, which you could add graphics items into (hence why we postfix all graphical elements with *GraphicsItem).

---

## Model-View-Controller + LevelManger

Here we (very roughly) follow the model-view-controller architecture using the Mediator and Observer pattern.

For each game object, we separate it into its graphical and logical components. Each side of the model observes and communicates with the other side, either directly (as in the case of `FireTruck` and `TruckGraphicsItem`) or through a thin interface class such as `Tile`. This is implemented using Qt’s signal and slot system.

<img width="1159" height="728" alt="image 3" src="https://github.com/user-attachments/assets/389206de-7694-4216-8d41-c525399b23e5" />

Moreover, all these items are being connected by the LevelManager (the Mediator), the central hub for spawning and connecting game objects and adding them to the scene (e.g., via the `spawnTilesAndConnect` or the `spawnVehicleAndConnect` method).

---
