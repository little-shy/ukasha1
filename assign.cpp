/*
 ============================================================
    ----- Recipe Book ----- C++ Console Program -----
   Features:
     - 10 Built-in Recipes
     - Choose What to Cook (browse built-ins)
     - Add Your Own Recipes (dynamic array, no limit)
     - View All (built-in + custom)
     - Search by Name
     - Delete Custom Recipes
     - File Handling to save/load custom recipes
 ============================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include "ASSIGN.hpp"
#include "ASSIGN1.hpp"
using namespace std;

// ─── CONSTANTS ───

const string FILE_NAME     = "my_recipes.txt";
const string SEPARATOR     = "===END===";
const int    MAX_CUSTOM    = 200;
const int    BUILTIN_COUNT = 10;

// ─── STRUCT ───

struct Recipe {
    string name;
    string category;
    string ingredients;
    string instructions;
    int    prepTime;   // in minutes
    int    servings;
};

// ─── DYNAMIC ARRAY STRUCT ───

struct RecipeArray {
    Recipe data[MAX_CUSTOM];
    int    size;
};

// ─── BUILT-IN RECIPES ───

Recipe builtIn[BUILTIN_COUNT] = {

    // Recipe 1

    {
        "Pakistani Chicken Biryani (Karachi Style)",

        "Main Course",

        "1kg bone-in chicken, 750g Basmati rice, 1 cup yogurt, 2 tbsp biryani masala, "
        "ginger-garlic paste, salt, red chili powder, dried plums (alu bukhara), "
        "sliced onions, chopped tomatoes, whole spices, food coloring, mint, lemon",

        "1. MARINATE: Mix chicken with yogurt, biryani masala, ginger-garlic paste, salt, chili, dried plums.\n"
        "   2. CURRY: Fry onions golden. Add chicken, saute 5 min. Add tomatoes + water; cook until tender.\n"
        "   3. PARBOIL RICE: Boil rice with whole spices and salt until 70-80% cooked. Drain.\n"
        "   4. LAYER: In heavy pot - half rice, all chicken curry, remaining rice. Add food coloring, mint, lemon.\n"
        "   5. DUM: Seal pot with foil. Steam on very low heat 15-20 min until fully fluffy.",
        90, 6
    },

    // Recipe 2

    {
        "Beef Nihari",

        "Main Course",

        "1kg beef shank with bones, ghee, ginger-garlic paste, Nihari masala, "
        "4-6 cups water, 1/2 cup wheat flour (atta), sliced onions, ginger, lemon, green chilies",

        "1. SAUTE: Heat ghee, add beef shank and ginger-garlic paste. Brown the meat well.\n"
        "   2. SPICES: Add Nihari masala, saute 1 min. Add water; bring to boil.\n"
        "   3. SLOW COOK: Low heat, cover, simmer 3-4 hours (pressure cooker: 45 min) until tender.\n"
        "   4. THICKEN: Mix wheat flour + water into slurry; stir slowly into stew until silky.\n"
        "   5. TARKA: Fry onions in ghee; pour over nihari. Garnish with ginger, lemon, chilies.",
        240, 4
    },

    // Recipe 3

    {
        "Chapli Kebab (Peshawari)",

        "BBQ / Snack",

        "500g minced beef (20% fat), chopped onions, tomatoes, green chilies, "
        "crushed coriander seeds, pomegranate seeds (anardana), cumin, salt, "
        "red chili flakes, 1 egg, 2 tbsp gram flour, tomato slices",

        "1. MIX: Combine minced beef with onions, tomatoes, and green chilies.\n"
        "   2. SEASON: Add coriander, anardana, cumin, salt, chili flakes, egg, gram flour.\n"
        "   3. KNEAD: Mix by hand 5 min to release meat proteins (prevents breaking).\n"
        "   4. SHAPE: Flatten into large thin disc; press a tomato slice into center.\n"
        "   5. SHALLOW FRY: Cook on tawa in hot oil/ghee 3-4 min per side until dark brown.",
        30, 4
    },

    // Recipe 4

    {
        "Chicken Karahi",

        "Main Course",

        "1kg chicken pieces, 1/2 cup oil, salt, ginger-garlic paste, "
        "4-5 large tomatoes, red chili flakes, black pepper, green chilies, "
        "ginger julienne, fresh coriander",

        "1. FLASH FRY: Heat oil; fry chicken with salt and ginger-garlic on HIGH heat until color changes.\n"
        "   2. TOMATOES: Add halved tomatoes (skin side up). Cover 5 min; remove softened skins.\n"
        "   3. BHUNA: Smash tomatoes to pulp. Add chili flakes, black pepper, green chilies.\n"
        "      Cook on HIGH heat, stirring constantly until water evaporates and oil separates.\n"
        "   4. FINISH: Add ginger julienne and coriander. Serve immediately with naan.",
        40, 4
    },

    // Recipe 5

    {
        "Haleem",

        "Main Course",

        "Wheat + barley + mixed lentils (soaked overnight), 500g beef or chicken, "
        "onions, ginger-garlic paste, haleem masala, fried onions, ginger, lemon, chaat masala",

        "1. GRAINS: Soak wheat, barley, lentils overnight. Boil until completely soft; mash into paste.\n"
        "   2. MEAT: Cook beef/chicken with onions, ginger-garlic, haleem spices until falling apart. Shred.\n"
        "   3. COMBINE: Mix shredded meat into grain paste.\n"
        "   4. GHOTNA: Stir and pound with wooden masher on low heat 30-60 min until smooth.\n"
        "   5. GARNISH: Top with fried onions, ginger, lemon, and chaat masala.",
        180, 6
    },

    // Recipe 6

    {
        "Gajar ka Halwa (Carrot Halwa)",
        "Dessert",

        "1kg red carrots (grated), 1 liter full-fat milk, cardamom pods, "
        "1/2 cup ghee, 1 cup sugar, khoya (milk solids), chopped nuts",

        "1. COOK: Put grated carrots in pot with milk and cardamom pods.\n"
        "   2. REDUCE: Simmer on medium heat, stirring, until milk almost fully evaporates.\n"
        "   3. FRY (BHUNA): Add ghee and sugar. Roast 10-15 min until deep red and ghee shines.\n"
        "   4. FINISH: Stir in khoya and chopped nuts. Serve warm.",
        75, 6
    },

    // Recipe 7

    {
        "Aloo Gosht (Meat and Potato Curry)",

        "Main Course",

        "1/2 kg mutton or beef, 1/2 cup oil, 2 sliced onions, 1 tbsp ginger-garlic paste, "
        "salt, 1.5 tsp red chili powder, 1 tsp coriander powder, 1/2 tsp turmeric, "
        "2 chopped tomatoes, 2 cups water, 3-4 potatoes, garam masala, fresh coriander",

        "1. SAUTE: Heat oil; fry onions golden. Add ginger-garlic paste, saute 1 min.\n"
        "   2. SEAR: Add meat on HIGH heat until color changes. Add all spices.\n"
        "   3. SIMMER: Add tomatoes and water. Cover, low heat 45-60 min until meat is 80% tender.\n"
        "   4. POTATOES: Add halved potatoes. Cook 15 more min until both are soft.\n"
        "   5. FINISH: Sprinkle garam masala and coriander. Serve with rice or roti.",
        75, 4
    },

    // Recipe 8

    {
        "Mutton Kunna (Chinioti Style)",

        "Main Course",

        "1kg mutton leg pieces, 1/2 cup ghee, 1 tsp black cumin (shah zeera), "
        "1 tbsp ginger-garlic paste, 1 tsp red chili powder, 1/2 tsp turmeric, "
        "1 tbsp coriander powder, salt, 4-5 cups water, 3 tbsp wheat flour, "
        "pinch of nutmeg and mace (jaifal/javitri)",

        "1. INITIAL COOK: Heat ghee; add shah zeera. Add mutton and ginger-garlic; fry until browned.\n"
        "   2. SPICE MIX: Add chili, turmeric, coriander, salt. Pour 4-5 cups water.\n"
        "   3. SLOW STEAM: Cover tightly; simmer on VERY LOW heat 3-4 hours until falls off bone.\n"
        "   4. THICKEN: Dissolve wheat flour in water; slowly stir into pot for silky gravy.\n"
        "   5. FINAL: Add nutmeg and mace for signature fragrance. Serve with khameeri naan.",
        240, 4
    },

    // Recipe 9

    {
        "Seekh Kabab",

        "BBQ / Snack",

        "1/2 kg fine minced beef or mutton (20% fat), 1 onion (squeezed dry), "
        "1 tbsp ginger-garlic paste, 2 chopped green chilies, 1/2 cup fresh coriander, "
        "1 tsp each cumin/coriander powder/red chili flakes/garam masala, 2 tbsp gram flour",

        "1. PREPARE: Squeeze all excess water from mince thoroughly.\n"
        "   2. MIX: Add onion (squeezed dry), ginger-garlic paste, green chilies, coriander.\n"
        "   3. SPICES: Add cumin, coriander powder, chili flakes, garam masala, gram flour.\n"
        "   4. MARINATE & SHAPE: Rest mixture 2 hours. Mold onto metal skewers into long cylinders.\n"
        "   5. GRILL: Grill over charcoal (or oven 200C) 10-12 min, brushing with oil until charred.",
        30, 4
    },

    // Recipe 10

    {
        "Zarda (Sweet Rice)",

        "Dessert",

        "500g Basmati rice, yellow food coloring, 4 cloves, 4 green cardamoms, "
        "1/4 cup ghee, 1.5 cups sugar, 1/4 cup milk or water, "
        "raisins, sliced almonds, pistachios, ashrafi or khoya",
        
        "1. BOIL RICE: Boil rice with yellow coloring, cloves, cardamoms until 90% cooked. Drain.\n"
        "   2. SYRUP: Heat ghee; add sugar and milk/water. Stir until sugar dissolves into syrup.\n"
        "   3. COMBINE: Add boiled rice to syrup; toss gently.\n"
        "   4. GARNISH: Top with raisins, almonds, pistachios, and candied fruit/khoya.\n"
        "   5. DUM: Cover; steam on very low heat 10-12 min until syrup absorbed and rice fluffy.",
        45, 6
    }

};

// ─── FUNCTION PROTOTYPES ───

void displayMainMenu();                       // Lines 299-312
void browseBuiltInRecipes();                  // Lines 315-348
void viewBuiltInDetail(int index);            // Lines 351-358
void addCustomRecipe(RecipeArray &arr);       // Lines 361-410
void viewAllCustom(RecipeArray &arr);         // Lines 413-436
void viewAllRecipes(RecipeArray &arr);        // Lines 439-465
void searchRecipes(RecipeArray &arr);         // Lines 468-517
void deleteCustomRecipe(RecipeArray &arr);    // Lines 520-571
void saveAllCustom(RecipeArray &arr);         // Lines 574-595
void loadCustomFromFile(RecipeArray &arr);    // Lines 598-630
void displayRecipeShort(Recipe r, int number);// Lines 633-640
void displayRecipeFull(Recipe r);             // Lines 643-654 

// ═══════════
//  MAIN
// ═══════════
int main() {
    RecipeArray customRecipes;
    customRecipes.size = 0;

    loadCustomFromFile(customRecipes);

    cout << "\n";
    printLine();
    cout << "      *** RECIPE BOOK ***\n";
    printLine();
    cout << "  " << BUILTIN_COUNT << " built-in recipes ready!\n";
    cout << "  " << customRecipes.size << " custom recipe(s) loaded from file.\n";
    printLine();

    int choice;
    do {
        displayMainMenu();
        cout << "  Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: browseBuiltInRecipes();            break;
            case 2: addCustomRecipe(customRecipes);    break;
            case 3: viewAllCustom(customRecipes);      break;
            case 4: viewAllRecipes(customRecipes);     break;
            case 5: searchRecipes(customRecipes);      break;
            case 6: deleteCustomRecipe(customRecipes); break;
            case 7:
                cout << "\n  Goodbye! Happy Cooking!\n\n";
                break;
            default:
                cout << "\n  [!] Invalid choice. Try again.\n";
                pauseScreen();
        }

    } while (choice != 7);

    return 0;
}

// ─── MAIN MENU ────────────────────────────────────────────
void displayMainMenu() {
    cout << "\n";
    printLine();
    cout << "             MAIN MENU\n";
    printLine();
    cout << "  1. Browse Built-in Recipes (What to Cook?)\n";
    cout << "  2. Add My Own Recipe\n";
    cout << "  3. View My Custom Recipes Only\n";
    cout << "  4. View ALL Recipes (Built-in + Custom)\n";
    cout << "  5. Search Any Recipe by Name\n";
    cout << "  6. Delete a Custom Recipe\n";
    cout << "  7. Exit\n";
    printLine();
}

// ─── BROWSE BUILT-IN RECIPES ──────────────────────────────
void browseBuiltInRecipes() {
    int choice;
    do {
        cout << "\n";
        printLine();
        cout << "     BUILT-IN PAKISTANI RECIPES\n";
        cout << "     What would you like to cook?\n";
        printLine();

        for (int i = 0; i < BUILTIN_COUNT; i++) {
            cout << "  " << (i + 1) << ". " << builtIn[i].name
                 << "\n     [" << builtIn[i].category
                 << " | Prep: " << builtIn[i].prepTime
                 << " min | Serves: " << builtIn[i].servings << "]\n\n";
        }

        cout << "  0. Back to Main Menu\n";
        printLine();
        cout << "  Enter number to view full recipe (0 to go back): ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        if (choice >= 1 && choice <= BUILTIN_COUNT) {
            viewBuiltInDetail(choice - 1);
        } else {
            cout << "\n  [!] Invalid. Enter 1-" << BUILTIN_COUNT << " or 0.\n";
        }

    } while (choice != 0);
}

// ─── VIEW BUILT-IN DETAIL ─────────────────────────────────
void viewBuiltInDetail(int index) {
    cout << "\n";
    printLine();
    displayRecipeFull(builtIn[index]);
    printLine();
    pauseScreen();
}

// ─── ADD CUSTOM RECIPE ────────────────────────────────────
void addCustomRecipe(RecipeArray &arr) {
    if (arr.size >= MAX_CUSTOM) {
        cout << "\n  [!] Storage full! Maximum " << MAX_CUSTOM << " custom recipes reached.\n";
        pauseScreen();
        return;
    }

    Recipe r;
    cout << "\n";
    printLine();
    cout << "       ADD YOUR OWN RECIPE\n";
    printLine();

    cout << "  Recipe Name       : ";
    getline(cin, r.name);

    cout << "  Category          : ";
    getline(cin, r.category);

    cout << "  Ingredients       : ";
    getline(cin, r.ingredients);

    cout << "  Instructions      : ";
    getline(cin, r.instructions);

    // ── Validated Prep Time input ──
    while (true) {
        cout << "  Prep Time (mins)  : ";
        cin >> r.prepTime;

        if (cin.fail() || r.prepTime <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Invalid input. Please enter a positive whole number (e.g. 30).\n";
        } else {
            cin.ignore();
            break;
        }
    }

    // ── Validated Servings input ──
    while (true) {
        cout << "  Servings          : ";
        cin >> r.servings;

        if (cin.fail() || r.servings <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Invalid input. Please enter a positive whole number (e.g. 4).\n";
        } else {
            cin.ignore();
            break;
        }
    }

    // Add to array
    arr.data[arr.size] = r;
    arr.size++;

    // Save to file
    saveAllCustom(arr);

    cout << "\n  [+] \"" << r.name << "\" added successfully!\n";
    cout << "  Total custom recipes stored: " << arr.size << "\n";
    pauseScreen();
}

// ─── VIEW CUSTOM RECIPES ONLY ─────────────────────────────
void viewAllCustom(RecipeArray &arr) {
    cout << "\n";
    printLine();
    cout << "    MY CUSTOM RECIPES (" << arr.size << " total)\n";
    printLine();

    if (arr.size == 0) {
        cout << "  [!] You have no custom recipes yet.\n";
        cout << "      Go to option 2 to add your first recipe!\n";
        pauseScreen();
        return;
    }

    for (int i = 0; i < arr.size; i++) {
        cout << "\n";
        displayRecipeFull(arr.data[i]);
        cout << "\n";
    }

    pauseScreen();
}

// ─── VIEW ALL (BUILT-IN + CUSTOM) ─────────────────────────
void viewAllRecipes(RecipeArray &arr) {
    cout << "\n";
    printLine();
    int total = BUILTIN_COUNT + arr.size;
    cout << "    ALL RECIPES (" << total << " total)\n";
    printLine();

    cout << "\n  ===== BUILT-IN RECIPES =====\n";
    for (int i = 0; i < BUILTIN_COUNT; i++) {
        displayRecipeShort(builtIn[i], i + 1);
    }

    cout << "\n  ===== MY CUSTOM RECIPES =====\n";
    if (arr.size == 0) {
        cout << "  (None added yet)\n";
    } else {
        for (int i = 0; i < arr.size; i++) {
            displayRecipeShort(arr.data[i], i + 1);
        }
    }

    pauseScreen();
}

// ─── SEARCH RECIPES ───────────────────────────────────────
void searchRecipes(RecipeArray &arr) {
    string query;
    cout << "\n";
    printLine();
    cout << "       SEARCH RECIPES\n";
    printLine();
    cout << "  Enter name to search: ";
    getline(cin, query);

    string qLower = query;
    for (char &c : qLower) c = tolower(c);

    bool found    = false;
    int  numFound = 0;

    cout << "\n  --- Results for \"" << query << "\" ---\n";

    // Search built-ins
    for (int i = 0; i < BUILTIN_COUNT; i++) {
        string rName = builtIn[i].name;
        for (char &c : rName) c = tolower(c);

        if (rName.find(qLower) != string::npos) {
            cout << "\n  [Built-in]\n";
            displayRecipeFull(builtIn[i]);
            found = true;
            numFound++;
        }
    }

    // Search custom recipes
    for (int i = 0; i < arr.size; i++) {
        string rName = arr.data[i].name;
        for (char &c : rName) c = tolower(c);

        if (rName.find(qLower) != string::npos) {
            cout << "\n  [My Recipe]\n";
            displayRecipeFull(arr.data[i]);
            found = true;
            numFound++;
        }
    }

    if (!found) {
        cout << "  [!] No recipe found matching \"" << query << "\".\n";
    } else {
        cout << "\n  Total results found: " << numFound << "\n";
    }

    pauseScreen();
}

// ─── DELETE CUSTOM RECIPE ─────────────────────────────────
void deleteCustomRecipe(RecipeArray &arr) {
    cout << "\n";
    printLine();
    cout << "      DELETE CUSTOM RECIPE\n";
    printLine();

    if (arr.size == 0) {
        cout << "  [!] No custom recipes to delete.\n";
        pauseScreen();
        return;
    }

    cout << "  Your custom recipes:\n\n";
    for (int i = 0; i < arr.size; i++) {
        cout << "  " << (i + 1) << ". " << arr.data[i].name
             << " [" << arr.data[i].category << "]\n";
    }
    cout << "  0. Cancel\n";
    printLine();
    cout << "  Enter number to delete: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) return;

    if (choice < 1 || choice > arr.size) {
        cout << "\n  [!] Invalid choice.\n";
        pauseScreen();
        return;
    }

    const Recipe *toDelete = &arr.data[choice - 1];   // pointer to the recipe being deleted
    string deletedName = toDelete->name;               // access name through pointer

    // Shift elements left to fill the gap
    for (int i = choice - 1; i < arr.size - 1; i++) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;

    // Rewrite file
    saveAllCustom(arr);

    cout << "\n  [+] \"" << deletedName << "\" deleted successfully!\n";
    cout << "  Remaining custom recipes: " << arr.size << "\n";
    pauseScreen();
}

// ─── SAVE ALL CUSTOM TO FILE ──────────────────────────────
void saveAllCustom(RecipeArray &arr) {
    ofstream file(FILE_NAME, ios::trunc);

    if (!file) {
        cout << "  [!] Error: Could not open file for saving.\n";
        return;
    }

    for (int i = 0; i < arr.size; i++) {
        const Recipe rPtr = arr.data[i];             // pointer to recipe being written to file
        file << rPtr.name         << "\n";
        file << rPtr.category     << "\n";
        file << rPtr.ingredients  << "\n";
        file << rPtr.instructions << "\n";
        file << rPtr.prepTime     << "\n";
        file << rPtr.servings     << "\n";
        file << SEPARATOR          << "\n";
    }

    file.close();
}

// ─── LOAD CUSTOM FROM FILE ────────────────────────────────
void loadCustomFromFile(RecipeArray &arr) {
    ifstream file(FILE_NAME);

    if (!file) {
        arr.size = 0;
        return;
    }

    arr.size = 0;
    string line;

    while (arr.size < MAX_CUSTOM &&
           getline(file, arr.data[arr.size].name)) {

        if (arr.data[arr.size].name.empty() ||
            arr.data[arr.size].name == SEPARATOR) continue;

        getline(file, arr.data[arr.size].category);
        getline(file, arr.data[arr.size].ingredients);
        getline(file, arr.data[arr.size].instructions);

        getline(file, line);
        arr.data[arr.size].prepTime = stoi(line);

        getline(file, line);
        arr.data[arr.size].servings = stoi(line);

        getline(file, line); // read SEPARATOR line

        arr.size++;
    }

    file.close();
}

// ─── DISPLAY RECIPE (SHORT - for lists) ───────────────────
void displayRecipeShort(Recipe r, int number) {
    cout << "  " << number << ". " << r.name
         << " [" << r.category << " | Prep: " << r.prepTime
         << " min | Serves: " << r.servings << "]\n";
}

// ─── DISPLAY RECIPE (FULL - for detail view) ──────────────
void displayRecipeFull(Recipe r) {
       cout << "  Name         : " << r.name        << "\n";
    cout << "  Category     : " << r.category    << "\n";
    cout << "  Prep Time    : " << r.prepTime    << " minutes\n";
    cout << "  Servings     : " << r.servings    << " people\n";
    cout << "  ------------------------------------------\n";
    cout << "  INGREDIENTS:\n  " << r.ingredients << "\n";
    cout << "  ------------------------------------------\n";
    cout << "  INSTRUCTIONS:\n  " << r.instructions << "\n";
}