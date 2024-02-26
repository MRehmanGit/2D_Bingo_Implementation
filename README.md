# 2D_Bingo_Implementation
Implements an American Bingo game using the Bingo class. Features include card initialization, randomization, and efficient ball drawing. The code ensures memory management, error handling, and adheres to C++ programming standards, providing a solid foundation for a complete gaming experience. 


Key Features:

Card Representation: Utilizes a 2D array (m_card) to store bingo card information, with each cell represented by the Cell class.
Efficiency Enhancement: Employs a secondary array (m_helper) to optimize ball number checks for faster runtime.
Tracking Empty Cells: Utilizes m_trackRows and m_trackCols arrays to monitor empty cells in rows and columns, facilitating game completion conditions.
Initialization and Randomization: Provides functions like initCard and reCreateCard to initialize cards with random numbers, allowing multiple games with varied parameters.
Drawing Balls: Generates a list of randomly distributed ball numbers, ensuring uniqueness within the specified range.
Gameplay Logic: The play function processes drawn ball numbers, updates the card state, and determines the winner based on the fewest replacements.
Memory Management: Implements constructors, destructor, and a clear function to handle memory allocation and deallocation.
Additional Information:

Error Handling: The constructors and initialization functions include error-checking mechanisms to ensure valid parameters and successful operations.
Assignment Operator: Overloads the assignment operator for deep copying, considering self-assignment protection.
Debugging Aid: The dumpCard function aids in debugging by rendering the current state of the card in the terminal.
