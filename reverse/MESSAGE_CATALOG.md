# MORIA DOS 1.9.8.7 — Complete Message Catalog

Extracted from `memory.dump` (CP850 encoding) and cross-referenced with
`MORIA_with_constants.C` (Ghidra decompilation).

## String Table Layout

- **Segment base**: DS = 0x22DE0
- **Encoding**: CP850 (Pascal-style: first byte = length, then text)
- **Lookup function**: `display_score_with_fatal(int message_id)` at line 155

### Offset Formulas (DS-relative, 16-bit signed → unsigned wrap)

| Region | ID Range | Formula | Stride |
|--------|----------|---------|--------|
| R1 | 0–100 | `id × 51 - 15287` (id × 0x33 - 0x3BB7) | 51 bytes |
| R2 | 101–300 | `(id-100) × 31 - 10677` ((id-100) × 0x1F - 0x29B5) | 31 bytes |
| R3 | 301–400 | `(id-300) × 73 - 17572` ((id-300) × 0x49 - 0x44A4) | 73 bytes |
| R4 | 401+ | `(id-400) × 16 - 7283` ((id-400) × 0x10 - 0x1C73) | 16 bytes |

Signed DS offsets wrap unsigned: `abs_addr = 0x22DE0 + (offset & 0xFFFF)`.

---

## Table of Contents

1. [Region 1: Scrolls, Potions, Actions (IDs 1–91)](#region-1-scrolls-potions-actions-ids-191)
2. [Region 2: Game Messages (IDs 101–210)](#region-2-game-messages-ids-101210)
3. [Region 3: Help, Long Messages (IDs 301–397)](#region-3-help-long-messages-ids-301397)
4. [Region 4: UI Labels (IDs 401–425)](#region-4-ui-labels-ids-401425)
5. [Item Description Table](#item-description-table)
6. [Randomization Tables](#randomization-tables)
7. [Cross-Reference: Message ID → C Code Usage](#cross-reference-message-id--c-code-usage)

---

## Region 1: Scrolls, Potions, Actions (IDs 1–91)

| ID | Hex | French Text | English Gloss |
|----|-----|-------------|---------------|
| 1 | 0x01 | Je ne vois pas de parchemins dans votre sac. | I don't see any scrolls in your bag. |
| 2 | 0x02 | Quel parchemin voulez-vous lire ? | Which scroll do you want to read? |
| 3 | 0x03 | Vous vous sentez plus calme, maintenant. | You feel calmer now. |
| 4 | 0x04 | Lire de la nourriture !? Ca ne va pas ? | Read food!? Are you crazy? |
| 5 | 0x05 | Vous ne pouvez pas. Le Huorn vous tient. | You can't. The Huorn holds you. |
| 6 | 0x06 | Mon Dieu que le monde est laid ! | God, the world is ugly! |
| 7 | 0x07 | Votre armure semble couverte d'un voile doré. | Your armor seems covered with a golden veil. |
| 8 | 0x08 | Votre arme vibre pendant un moment. | Your weapon vibrates for a moment. |
| 9 | 0x09 | Tiens, mais il y a une carte, sur ce parchemin! | Hey, there's a map on this scroll! |
| 10 | 0x0A | C'est un parchemin d'identification | It's an identification scroll |
| 11 | 0x0B | ... mais il n'y a plus rien dans votre chargement! | ...but there's nothing left in your inventory! |
| 12 | 0x0C | Vous y voyez un peu plus clair. | You see a little more clearly. |
| 13 | 0x0D | Il n'y a rien d'écrit sur ce parchemin. | There's nothing written on this scroll. |
| 14 | 0x0E | Ah! Ah! Ah! Vous êtes bien eu, non ? | Ha! Ha! Ha! Got you, didn't I? |
| 15 | 0x0F | Eh oui, le parchemin fou a encore frappé !!! | Oh yes, the crazy scroll strikes again!!! |
| 16 | 0x10 | Bouh ! | Boo! |
| 17 | 0x11 | Zut à celui qui m'a lu. | Damn whoever read me. |
| 18 | 0x12 | Dommage. | Too bad. |
| 19 | 0x13 | C'est un parchemin recyclé, offert par MORIA Ltd. | It's a recycled scroll, courtesy of MORIA Ltd. |
| 20 | 0x14 | Une musique céleste vous assourdit. | Celestial music deafens you. |
| 21 | 0x15 | Il ne se passe pas grand chose d'intéressant. | Nothing very interesting happens. |
| 22 | 0x16 | Et où voulez-vous que je trouve une potion ? | Where do you want me to find a potion? |
| 23 | 0x17 | Quelle potion voulez-vous boire ? | Which potion do you want to drink? |
| 24 | 0x18 | Mais qu'est ce que je fous là ???! | What the hell am I doing here???! |
| 25 | 0x19 | Vous n'avez absolument rien à manger. | You have absolutely nothing to eat. |
| 26 | 0x1A | Expliquez-moi donc comment boire ça ! | Explain to me how to drink that! |
| 27 | 0x1B | Il vous faudrait pour cela une baguette.... | You would need a wand for that.... |
| 28 | 0x1C | Vous n'avez pas d'anneau à cette main. | You don't have a ring on that hand. |
| 29 | 0x1D | Mais! Vous ne portez aucun anneau ! | But! You're not wearing any ring! |
| 30 | 0x1E | Vous vous sentez vraiment en pleine forme ! | You feel really in top shape! |
| 31 | 0x1F | Enfin quoi ! Vous l'avez déjà enfilé ! | Come on! You've already put it on! |
| 32 | 0x20 | Ce n'est pas un escalier de descente. | This is not a descending staircase. |
| 33 | 0x21 | Vous allez souffrir, si vous essayez d'enfiler ça! | You'll suffer if you try to put that on! |
| 34 | 0x22 | Vous n'avez aucun anneau a enfiler. | You have no ring to put on. |
| 35 | 0x23 | Trouvez d'abord une armure à mettre. | Find armor to wear first. |
| 36 | 0x24 | Argh... ça va vraiment très mal. | Argh... things are really bad. |
| 37 | 0x25 | Wait a little minute, while I dig the Moria... | *(English in original)* |
| 38 | 0x26 | Donnez-moi quelque chose de plausible : | Give me something plausible: |
| 39 | 0x27 | Mais ... qui suis-je ? Où suis-je | But... who am I? Where am I? |
| 40 | 0x28 | Ca ne peut pas être votre nom ! | That can't be your name! |
| 41 | 0x29 | Vous ne pouvez plus bouger d'un poil. | You can't move at all. |
| 42 | 0x2A | Salut, téméraire aventurier .... | Hello, bold adventurer.... |
| 43 | 0x2B | Vous allez entrer dans le labyrinthe de la Moria. | You are about to enter the labyrinth of Moria. |
| 44 | 0x2C | ... mais auparavant, veuillez me donner votre nom, | ...but first, please give me your name, |
| 45 | 0x2D | il me sera utile pour inscrire sur votre tombe ... | it will be useful to inscribe on your tombstone... |
| 46 | 0x2E | Jamais vous ne réussirez à enfiler ça. | You'll never manage to put that on. |
| 47 | 0x2F | Un lourd voile de ténèbres s'abat sur vous. | A heavy veil of darkness falls upon you. |
| 48 | 0x30 | Miam, en voilà une bonne potion ! | Yum, that's a good potion! |
| 49 | 0x31 | L'air semble soudain plus dense. | The air suddenly seems denser. |
| 50 | 0x32 | Vous vous sentez très maladroit. | You feel very clumsy. |
| 51 | 0x33 | Vous avez des difficultés à respirer. | You have difficulty breathing. |
| 52 | 0x34 | Avoir des explications sur le jeu → entrez E | Get game explanations → enter E |
| 53 | 0x35 | Consulter la table des scores → entrez S | View high scores → enter S |
| 54 | 0x36 | Commencer à jouer → entrez J | Start playing → enter J |
| 55 | 0x37 | Finir → entrez F | Quit → enter F |
| 56 | 0x38 | Beuh.. ça a vraiment un goût abominable. | Eww... it really tastes horrible. |
| 57 | 0x39 | Bof ! Pas terrible, mais enfin... | Meh! Not great, but still... |
| 58 | 0x3A | Mmm... Pas mauvais du tout. | Mmm... Not bad at all. |
| 59 | 0x3B | Ah bravo ! Mes compliments au Chef ! | Bravo! My compliments to the Chef! |
| 60 | 0x3C | Désolé, on ne peut pas remonter par là. | Sorry, can't go back up this way. |
| 61 | 0x3D | Quelle armure voulez-vous revêtir ? | Which armor do you want to wear? |
| 62 | 0x3E | Sauron a pris possession de votre volonté. | Sauron has taken possession of your will. |
| 63 | 0x3F | Quel objet voulez-vous renommer ? | Which item do you want to rename? |
| 64 | 0x40 | Vous ne pouvez pas renommer cela. | You can't rename that. |
| 65 | 0x41 | ... mais la rouille disparait instantanément. | ...but the rust disappears instantly. |
| 66 | 0x42 | Que voulez-vous donc identifier ? | What do you want to identify? |
| 67 | 0x43 | Quelle arme voulez-vous brandir ? | Which weapon do you want to wield? |
| 68 | 0x44 | Je ne considère pas cela comme une arme. | I don't consider that a weapon. |
| 69 | 0x45 | Vous êtes devenu esclave de l'Anneau | You've become a slave of the Ring |
| 70 | 0x46 | Mais ! Vous ne portez pas d'armure ! | But! You're not wearing armor! |
| 71 | 0x47 | Votre tête heurte le plafond, et ça fait mal. | Your head hits the ceiling, and it hurts. |
| 72 | 0x48 | Une tornade s'abat soudainement sur vous. | A tornado suddenly hits you. |
| 73 | 0x49 | L'Oeil de Sauron vous transperce l'ame. | The Eye of Sauron pierces your soul. |
| 74 | 0x4A | ... mais vous n'avez plus de place. | ...but you have no more room. |
| 75 | 0x4B | Vous n'avez même plus un seul objet à abandonner. | You don't even have a single item to drop. |
| 76 | 0x4C | Il y a déjà quelque chose à cet endroit. | There's already something in this spot. |
| 77 | 0x4D | Quel objet voulez-vous abandonner ? | Which item do you want to drop? |
| 78 | 0x4E | Impossible, cet anneau porte un maléfice. | Impossible, this ring bears a curse. |
| 79 | 0x4F | Un sort vous en empêche ! | A spell prevents you! |
| 80 | 0x50 | Vous commencez à être affaibli. | You're starting to weaken. |
| 81 | 0x51 | Vous commencez à avoir faim ... | You're starting to get hungry... |
| 82 | 0x52 | tapez espace pour la suite, f pour finir | press space to continue, f to finish |
| 83 | 0x53 | Vous ne pouvez rien lancer dans cette direction | You can't throw anything in that direction |
| 84 | 0x54 | L'anneau se met en place de lui même. | The ring puts itself on. |
| 85 | 0x55 | Vous vous sentez beaucoup plus adroit. | You feel much more dexterous. |
| 86 | 0x56 | Votre armure explose !.(gnarf gnarf gnarf) | Your armor explodes! (gnarf gnarf gnarf) |
| 87 | 0x57 | Que voulez vous enlever? (a - h - c - g) | What do you want to remove? (a-h-c-g) |
| 88 | 0x58 | Vous ne réussissez qu'à vous tordre le cou ! | You only manage to twist your neck! |
| 89 | 0x59 | Vous avez déjà tous ce qu'il vous faut !. | You already have everything you need! |
| 90 | 0x5A | Oh! Comme tout devient clair maintenant! | Oh! How everything becomes clear now! |
| 91 | 0x5B | Comment le nommez-vous ? | What do you name it? |

---

## Region 2: Game Messages (IDs 101–210)

| ID | Hex | French Text | Context |
|----|-----|-------------|---------|
| 101 | 0x65 | Comment le nommez-vous ? | Rename prompt |
| 102 | 0x66 | Désolé, ça ne se boit pas ... | Sorry, you can't drink that |
| 103 | 0x67 | Ca, c'est un chouette trip ! | That's a great trip! (potion) |
| 104 | 0x68 | Vous vous sentez bien mieux. | You feel much better. (heal) |
| 105 | 0x69 | Cette came est impec, non ? | This stuff is great, right? |
| 106 | 0x6A | Hey, bonjour Superman! | Hey, hello Superman! |
| 107 | 0x6B | Waah, super, je plane.. | Whoa, cool, I'm flying.. |
| 108 | 0x6C | Oh! Quelle puissance ! | Oh! What power! |
| 109 | 0x6D | Dur, dur, je flippe... | Tough, I'm freaking out... |
| 110 | 0x6E | Bad trip ! | Bad trip! |
| 111 | 0x6F | Hein, quoi, où vais-je ? | Huh, what, where am I going? |
| 112 | 0x70 | Waah ! Laissez moi partir ! | Whoa! Let me go! |
| 113 | 0x71 | Vous respirez mieux. | You breathe easier. |
| 114 | 0x72 | Votre coeur bat comme un fou. | Your heart beats wildly. |
| 115 | 0x73 | Vous vous sentez plus habile. | You feel more skilled. |
| 116 | 0x74 | Comment la renommez-vous ? | What do you rename it? |
| 117 | 0x75 | Vous avez trouvé | You found |
| 118 | 0x76 | Vous laissez | You leave |
| 119 | 0x77 | C'est déjà identifié. | It's already identified. |
| 120 | 0x78 | Vous l'avez déjà à la main. | You already have it in hand. |
| 121 | 0x79 | Ah non ! Pas plus d'une ! | Oh no! Not more than one! |
| 122 | 0x7A | Vous portez maintenant | You are now wearing |
| 123 | 0x7B | Table des scores | High scores |
| 124 | 0x7C | Vous désirez : | You want: |
| 125 | 0x7D | votre choix : | your choice: |
| 126 | 0x7E | tué par | killed by |
| 127 | 0x7F | mort de faim | died of hunger |
| 128 | 0x80 | mort de lassitude | died of boredom |
| 129 | 0x81 | mort d'épuisement | died of exhaustion |
| 130 | 0x82 | mort de soif | died of thirst |
| 131 | 0x83 | noyé | drowned |
| 132 | 0x84 | sorti de Moria | left Moria |
| 133 | 0x85 | mort stupidement | died stupidly |
| 134 | 0x86 | mort de gourmandise | died of gluttony |
| 135 | 0x87 | asservi par l'Anneau | enslaved by the Ring |
| 136 | 0x88 | Vous avez été tué par | You were killed by |
| 137 | 0x89 | Vous êtes mort de faim | You starved to death |
| 138 | 0x8A | Vous avez renoncé à la vie | You gave up on life |
| 139 | 0x8B | Vous êtes mort d'épuisement | You died of exhaustion |
| 140 | 0x8C | Vous êtes mort de soif | You died of thirst |
| 141 | 0x8D | Vous vous êtes noyé | You drowned |
| 142 | 0x8E | Vous avez gagné. | You won. |
| 143 | 0x8F | Vous êtes mort par imprudence | You died of carelessness |
| 144 | 0x90 | Vous êtes mort de boulimie | You died of overeating |
| 145 | 0x91 | Bienvenue au niveau | Welcome to level |
| 146 | 0x92 | Vous avez abandonné | You abandoned |
| 147 | 0x93 | Eh! Mais c'est Sauron ! | Hey! But that's Sauron! |
| 148 | 0x94 | Votre armure rouille ! | Your armor rusts! |
| 149 | 0x95 | Vous vous sentez affaibli. | You feel weakened. |
| 150 | 0x96 | On vous taxe | You're being robbed |
| 151 | 0x97 | Il vous a taxé | He robbed you |
| 152 | 0x98 | Vous loupez le monstre. | You miss the monster. |
| 153 | 0x99 | Voilà qui m'étonnerait, car | That would surprise me, because |
| 154 | 0x9A | Et où voulez vous le mettre ? | Where do you want to put it? |
| 155 | 0x9B | Quel anneau enfiler ? | Which ring to put on? |
| 156 | 0x9C | Vous avez enfilé | You put on |
| 157 | 0x9D | Lequel ? | Which one? |
| 158 | 0x9E | Avec quelle baguette ? | With which wand? |
| 159 | 0x9F | Dans quelle direction ? | In which direction? |
| 160 | 0xA0 | Vous prenez une bûche. | You get hit hard. (lit: "take a log") |
| 161–170 | | *(High score death messages — 3rd person)* | |
| 171 | 0xAB | Vous êtes évanoui. | You fainted. |
| 172 | 0xAC | Hips ! Oh, pardon ... | Hic! Oh, sorry... |
| 173 | 0xAD | Ahh! Ça fait vraiment du bien! | Ahh! That really feels good! |
| 174 | 0xAE | Vous n'avez rien a brandir. | You have nothing to wield. |
| 175 | 0xAF | Vous avez maintenant | You now have |
| 176 | 0xB0 | Pepito := Ducon | *(Easter egg — debug rename)* |
| 177 | 0xB1 | Vous pouvez bouger de nouveau. | You can move again. |
| 178 | 0xB2 | Quel objet voulez-vous lancer? | What item do you want to throw? |
| 179 | 0xB3 | Vous tapez sur quelque chose. | You hit something. |
| 180 | 0xB4 | Ouf, ça va un peu mieux... | Phew, a little better... |
| 181 | 0xB5 | Vous avez tué | You killed |
| 182 | 0xB6 | Tableau de chasse de | Kill list of |
| 183 | 0xB7 | Un peu de nourriture. | Some food. |
| 184 | 0xB8 | Vous portiez | You were wearing |
| 185 | 0xB9 | Vous frappez | You strike |
| 186 | 0xBA | Vous avez atteint un monstre. | You hit a monster. |
| 187 | 0xBB | Vous n'avez rien ! | You have nothing! |
| 188 | 0xBC | Vous manquez | You miss |
| 189 | 0xBD | Vous avez atteint | You hit |
| 190 | 0xBE | (enfilé) | (worn) |
| 191 | 0xBF | Vous brillez de mille feux. | You shine with a thousand lights. |
| 192 | 0xC0 | -- encore -- | -- more -- |
| 193 | 0xC1 | (* pour la liste) | (* for list) |
| 194 | 0xC2 | Vous désirez vraiment | Do you really want |
| 195 | 0xC3 | Vous commencez a avoir soif. | You're starting to get thirsty. |
| 196 | 0xC4 | A boire, vite, par pitié ! | Something to drink, quick, please! |
| 197 | 0xC5 | Pouâh! Quelle horreur! | Ugh! How horrible! |
| 198 | 0xC6 | Vos doigts s'engourdissent... | Your fingers go numb... |
| 199 | 0xC7 | Votre bras s'alourdit. | Your arm grows heavy. |
| 200 | 0xC8 | Elle est trop petite ! | It's too small! |
| 201 | 0xC9 | Auriez vous deux têtes ??? | Do you have two heads??? |
| 202 | 0xCA | Le monstre vous gêne ! | The monster is in the way! |
| 203 | 0xCB | Mais vous n'en portez pas ! | But you're not wearing any! |
| 204 | 0xCC | Quel charabia ce parchemin ! | What gibberish on this scroll! |
| 205 | 0xCD | Vous vous sentez plus bête... | You feel dumber... |
| 206 | 0xCE | devenu fou furieux | gone raving mad |
| 207 | 0xCF | Vous êtes devenu fou | You've gone mad |
| 208 | 0xD0 | s'est mis à baver | started drooling |
| 209 | 0xD1 | Un de vos doigts repousse. | One of your fingers grows back. |
| 210 | 0xD2 | Force : | Strength: |

---

## Region 3: Help, Long Messages (IDs 301–397)

| ID | Hex | French Text |
|----|-----|-------------|
| 301 | 0x12D | Il n'y a pas d'objet de ce nom dans votre chargement. |
| 302 | 0x12E | Il n'y a rien de spécialement intéressant à lire là dessus. |
| 303 | 0x12F | Votre armure brille d'un eclat argenté pendant un instant. |
| 304 | 0x130 | Pouf! le parchemin disparait dans un nuage de fumée... |
| 305 | 0x131 | Il faut être un très bon magicien, pour lancer un sort avec ça. |
| 306 | 0x132 | Vous vous sentez plus fort. Whaoo! Quels muscles!.. |
| 307 | 0x133 | Wao, quel trip, les mecs. C'est le super pied, ce bled .. |
| 308 | 0x134 | a abandonner un objet |
| 309 | 0x135 | b boire une potion / l lire un parchemin |
| 310 | 0x136 | B brandir une arme / i,* faire l'inventaire |
| 311 | 0x137 | e enlever une armure / r revêtir une armure |
| 312 | 0x138 | E enfiler un anneau / N eNlever un anneau |
| 313 | 0x139 | m manger quelque chose |
| 314 | 0x13A | R renommer un objet |
| 315 | 0x13B | c fiche de personage |
| 316 | 0x13C | ? liste des commandes / s table des scores |
| 317 | 0x13D | L lancer un sort / T lancer un objet |
| 318 | 0x13E | > monter / < descendre |
| 319 | 0x13F | 2 ↓ mouvement vers le bas de l'écran |
| 320 | 0x140 | 4 ← mouvement vers la gauche de l'écran |
| 321 | 0x141 | 6 → mouvement vers la droite de l'écran |
| 322 | 0x142 | 8 ↑ mouvement vers le haut de l'écran |
| 323 | 0x143 | . rester sur place |
| 324 | 0x144 | ^G couper/retablir le son / ^T tableau de chasse |
| 325 | 0x145 | ^S se suicider / ^F abandonner la partie |
| 326 | 0x146 | ^P raffraichir l'écran / ^H help... |
| 327 | 0x147 | Impossible. Il semble que votre armure soit ensorcellée. |
| 328 | 0x148 | Vous êtes trop chargé, vous devez laisser du matériel. |
| 329 | 0x149 | MORIA (TM) Version 1.9.8.7 Copyright AJM86 |
| 330 | 0x14A | Désolé: le fichier MORIA.TXT n'est pas sur votre disquette. |
| 331 | 0x14B | Vous commencez à recupérer votre sens de l'orientation |
| 332 | 0x14C | Je ne vois pas de parchemins dans votre sac. |

---

## Region 4: UI Labels (IDs 401–425)

| ID | Hex | French Text | Usage |
|----|-----|-------------|-------|
| 401 | 0x191 | Force : | Stat label (strength) |
| 402 | 0x192 | Armure | Stat label (armor) |
| 403 | 0x193 | ration | Item display: food ration |
| 404 | 0x194 | alimentaire | Item display: food adjective |
| 405 | 0x195 | (en service) | Equipment: "(equipped)" |
| 406 | 0x196 | potion | Item type label |
| 407 | 0x197 | parchemin | Item type label |
| 408 | 0x198 | renommé | "renamed" |
| 409 | 0x199 | intitulé | "titled" |
| 410 | 0x19A | un anneau | "a ring" |
| 411 | 0x19B | renommé | "renamed" |
| 412 | 0x19C | une baguette | "a wand" |
| 413 | 0x19D | renommée | "renamed" (fem.) |
| 414 | 0x19E | Un Silmaril | "A Silmaril" |
| 415 | 0x19F | pièces d'or | "gold coins" |
| 416 | 0x1A0 | en finir ? | "end it?" |
| 417 | 0x1A1 | terminer ? | "finish?" |
| 418 | 0x1A2 | Version 4.1.1 | Version string |
| 419 | 0x1A3 | Quel Dommage ! | "What a pity!" |
| 420 | 0x1A4 | vous a volé | "stole from you" |
| 421 | 0x1A5 | Vous aviez | "You had" |
| 422 | 0x1A6 | Hmpfff ! | *(falling sound)* |
| 423 | 0x1A7 | Aaarrgh !! | *(death scream)* |
| 424 | 0x1A8 | des gantelets | "gauntlets" |
| 425 | 0x1A9 | Surprenant !... | "Surprising!..." |

---

## Item Description Table

**Base address**: 0x2A967 (DS-relative). **Stride**: 29 bytes. Pascal-style strings.

### Potion Effects (indices 0–23)

| # | French | English |
|---|--------|---------|
| 0 | de guérison | healing |
| 1 | d'extra-guérison | greater healing |
| 2 | de constitution | constitution |
| 3 | de force | strength |
| 4 | de confusion | confusion |
| 5 | empoisonnée | poisoned |
| 6 | amnésiante | amnesia |
| 7 | paralysante | paralyzing |
| 8 | accélérante | speed |
| 9 | ralentissante | slowing |
| 10 | hallucinogène | hallucinogenic |
| 11 | aveuglante | blinding |
| 12 | nourrissante | nourishing |
| 13 | d'expérience | experience |
| 14 | de perte de niveau | level drain |
| 15 | d'extralucidité | clairvoyance |
| 16 | de désorientation | disorientation |
| 17 | passe muraille | wall-phasing |
| 18 | de lévitation | levitation |
| 19 | désaltérante | thirst-quenching |
| 20 | d'invisibilité | invisibility |
| 21 | gazéifiante | gasifying |
| 22 | de dexterité | dexterity |
| 23 | de régénération | regeneration |

### Scroll Effects (indices 24–51)

| # | French | English |
|---|--------|---------|
| 24 | pour enchanter les armures | enchant armor |
| 25 | pour protéger les armures | protect armor |
| 26 | pour enchanter son arme | enchant weapon |
| 27 | topographique | topographic (map) |
| 28 | d'identification | identification |
| 29 | de teleportation | teleportation |
| 30 | d'hyper téléportation | hyper teleportation |
| 31 | pour invoquer un monstre | summon monster |
| 32 | de protection | protection |
| 33 | pour détecter la magie | detect magic |
| 34 | pour détecter la nouriture | detect food |
| 35 | pour repérer les monstres | detect monsters |
| 36 | pour détecter l'or | detect gold |
| 37 | d'ensorcellement | enchantment (curse) |
| 38 | de sommeil | sleep |
| 39 | vierge | blank |
| 40 | pour enlever les sorts | remove spells |
| 41 | de démolition | demolition |
| 42 | de destruction | destruction |
| 43 | pour effrayer les monstres | scare monsters |
| 44 | d'éparpillement | scattering |
| 45 | pour enchanter les anneaux | enchant rings |
| 46 | de dégradation d'anneaux | ring degradation |
| 47 | d'intelligence | intelligence |
| 48 | pour protéger son armure | protect one's armor |
| 49 | pour conserver sa force | preserve strength |
| 50 | pour ralentir sa digestion | slow digestion |
| 51 | d'augmentation des dégats | increase damage |

### Ring Effects (indices 52–66)

| # | French | English |
|---|--------|---------|
| 52 | de téléportation | teleportation |
| 53 | d'invisibilité | invisibility |
| 54 | de protection | protection |
| 55 | d'identification | identification |
| 56 | de régénération | regeneration |
| 57 | de détection de trappes | trap detection |
| 58 | de monstres | monsters |
| 59 | coupe doigt | finger-cutter |
| 60 | anti feu | anti-fire |
| 61 | de chute de plume | feather fall |
| 62 | de résurrection | resurrection |
| 63 | de nage | swimming |
| 64 | de rayon X | X-ray |
| 65 | de lévitation | levitation |
| 66 | de faiblesse | weakness |

### Wand Effects (indices 72–93)

| # | French | English |
|---|--------|---------|
| 72 | de téléportation | teleportation |
| 73 | de transmorphie | transmorph |
| 74 | de destruction | destruction |
| 75 | pour créer des murs | create walls |
| 76 | de ralentissement de monstre | slow monster |
| 77 | d'accélération de monstre | haste monster |
| 78 | d'affaiblissement | weakening |
| 79 | pour effrayer | frighten |
| 80 | de sourcier | dowsing |
| 81 | d'invocation de monstre | summon monster |
| 82 | d'invocation d'objet | summon object |
| 83 | de combat | combat |
| 84 | pour combler les trappes | fill traps |
| 85 | assoupissante | sleep-inducing |
| 86 | paralysante | paralyzing |
| 87 | d'invisibilité | invisibility |
| 88 | de création de trappes | create traps |
| 89 | de renforcement | reinforcement |
| 90 | capricieuse | capricious |
| 91 | d'illusion | illusion |
| 92 | de purification | purification |
| 93 | d'absorption d'énergie | energy drain |

### Armor Types (indices 96–106)

| # | French |
|---|--------|
| 96 | une armure de cuir |
| 97 | une armure de cuir renforcé |
| 98 | une cotte de mailles |
| 99 | une armure de fer |
| 100 | une cuirasse d'acier |
| 101 | une armure de Mithril |
| 102 | un heaume |
| 103 | une cape elfique |
| 104 | des gantelets de dextérité |
| 105 | des gantelets de maladresse |
| 106 | des gantelets de force |

### Weapon Types (indices 120–134)

| # | French |
|---|--------|
| 120 | un poignard |
| 121 | une dague |
| 122 | une lance |
| 123 | une massue |
| 124 | un sabre |
| 125 | un cimeterre |
| 126 | une épée |
| 127 | une épée à deux mains |
| 128 | une épée elfique |
| 129 | une hache |
| 130 | un arc |
| 131 | fleche |
| 132 | une dague elfique |
| 133 | une épée de glace |
| 134 | une épée vampirique |

### Ring Materials (indices 144–153)

| # | French |
|---|--------|
| 144 | de chance |
| 145 | de dessèchement |
| 146 | de monstres |
| 147 | d'annulation |
| 148 | de faim |
| 149 | de force |
| 150 | de régénération |
| 151 | de vulnérabilité |
| 152 | d'antimagie |
| 153 | d'expérience |

---

## Randomization Tables

**Stride**: 16 bytes. Both base and shuffled copies exist in memory.

### Potion Colors (24 colors)

rouge, blanche, gludure, brune, verte, noire, fluorescente, argentee,
orange, violette, incolore, mordoree, bleue, mauve, rose, grise,
jaune, chinée, cuivrée, moirée, beige, dorée, multicolore, albatre

### Ring Materials (19 materials)

d'or, d'argent, de platine, de jaspe, de rubis, de saphir, d'onyx,
d'opale, d'ivoire, de diamant, d'émeraude, de bronze, de jade,
de mithril, d'os, d'adamantite, d'agathe, de cristal, d'étain

### Wand Woods (22 woods)

de chêne, de peuplier, de teck, de saule, de merisier, de châtaigner,
de frêne, de noisetier, de charme, de cerisier, d'acajou, de pin,
d'olivier, d'érable, de platane, d'if, de hêtre, d'orme, de bambou,
de verre, de rose noire, de roseau

### Gems (10 gems)

un rubis, une émeraude, un diamant, un topaze, un saphir,
une agathe, une améthyste, un chrysobéryl, une turquoise, une opale

---

## Cross-Reference: Message ID → C Code Usage

Sorted by message ID. Only statically-determinable IDs listed (excludes computed `value + offset` patterns).

| ID | Hex | String (truncated) | Line(s) | Context |
|----|-----|--------------------|---------|---------|
| 2 | 0x02 | Quel parchemin lire? | 10684 | Scroll read prompt |
| 3 | 0x03 | Sentez plus calme | 12072 | Scroll effect: calm |
| 4 | 0x04 | Lire de la nourriture? | 10791 | Error: read food |
| 5 | 0x05 | Le Huorn vous tient | 11836 | Huorn prevents movement |
| 6 | 0x06 | Monde est laid | 12078 | Scroll effect: ugly world |
| 7 | 0x07 | Armure voile doré | 9593 | Scroll: protect armor |
| 8 | 0x08 | Arme vibre | 9600 | Scroll: enchant weapon |
| 12 | 0x0C | Voyez plus clair | 12085 | Scroll: light/detect |
| 20 | 0x14 | Musique céleste | 9857 | Wand: summon |
| 21 | 0x15 | Rien d'intéressant | 8937 | Wand: no charges |
| 23 | 0x17 | Quelle potion boire? | 10687 | Potion drink prompt |
| 24 | 0x18 | Qu'est-ce que je fous là | 12091 | Scroll effect: confusion |
| 25 | 0x19 | Rien à manger | 8328 | Error: no food |
| 26 | 0x1A | Comment boire ça | 10814 | Error: wrong item type |
| 28 | 0x1C | Pas d'anneau à cette main | 8552 | Error: no ring |
| 29 | 0x1D | Aucun anneau ! | 8527 | Error: no rings |
| 30 | 0x1E | Pleine forme | 10118 | Potion: greater heal (normal) |
| 31 | 0x1F | Déjà enfilé | 8478 | Error: already wearing |
| 32 | 0x20 | Pas escalier descente | 12249 | Error: wrong stairs |
| 33 | 0x21 | Souffrir enfiler ça | 10830 | Wand: pain effect |
| 38 | 0x26 | Quelque chose plausible | 3522 | Character creation: name prompt |
| 39 | 0x27 | Qui suis-je? | 10191 | Potion: confusion |
| 41 | 0x29 | Ne pouvez plus bouger | 10248 | Potion: paralysis (normal) |
| 42 | 0x2A | Salut, téméraire | 3465 | Intro: loop flag+0x2a (IDs 42–45) |
| 46 | 0x2E | Jamais enfiler ça | 10852 | Wand: cursed ring |
| 47 | 0x2F | Voile de ténèbres | 10293 | Potion: blindness |
| 48 | 0x30 | Bonne potion! | 10299 | Potion: food/stamina |
| 49 | 0x31 | Air plus dense | 10277 | Potion: haste (when paralyzed → cure) |
| 50 | 0x32 | Très maladroit | 6018 | `lose_experience_level` |
| 51 | 0x33 | Difficultés respirer | 10271 | Potion: speed (normal) |
| 52 | 0x34 | Explications jeu → E | 12626 | Main menu loop (IDs 52–55) |
| 60 | 0x3C | Pas remonter par là | 12277 | Error: can't go up |
| 61 | 0x3D | Quelle armure revêtir? | 10702 | Wear armor prompt |
| 62 | 0x3E | Sauron volonté | 6588 | Fear attack (severe) |
| 63 | 0x3F | Quel objet renommer? | 10708 | Rename prompt |
| 64 | 0x40 | Pas renommer | 7710 | Error: can't rename |
| 65 | 0x41 | Rouille disparait | 6086 | Shield: rust immune |
| 66 | 0x42 | Identifier? | 10705 | Identify prompt |
| 67 | 0x43 | Quelle arme brandir? | 10699 | Wield weapon prompt |
| 68 | 0x44 | Pas une arme | 10844 | Error: not a weapon |
| 69 | 0x45 | Esclave Anneau | 1982 | Display: ring slave |
| 70 | 0x46 | Pas d'armure | 8089 | Error: no armor worn |
| 71 | 0x47 | Tête heurte plafond | 10345 | Potion: levitation bump |
| 73 | 0x49 | Oeil de Sauron | 6593 | Fear attack (mild) |
| 74 | 0x4A | Plus de place | 7452 | Error: inventory full |
| 77 | 0x4D | Quel objet abandonner? | 10711 | Drop item prompt |
| 78 | 0x4E | Anneau maléfice | 693, 8573 | Error: cursed ring |
| 79 | 0x4F | Sort empêche | 668, 8287 | Error: spell prevents action |
| 82 | 0x52 | Espace suite, f finir | 5299 | Pagination prompt |
| 85 | 0x55 | Plus adroit | 10439 | Potion: dexterity up |
| 87 | 0x57 | Que voulez enlever? | 8177 | Unequip prompt |
| 88 | 0x58 | Tordre le cou | 8244 | Unequip: armor stuck |
| 104 | 0x68 | Sentez bien mieux | 10090, 10121 | Potion: heal (normal/confused) |
| 106 | 0x6A | Bonjour Superman | 10146 | Potion: stamina (confused) |
| 108 | 0x6C | Quelle puissance | 10159 | Potion: restore food (normal) |
| 109 | 0x6D | Dur, je flippe | 10465 | Potion use (confused) |
| 110 | 0x6E | Bad trip | 10180 | Potion: speed (confused) |
| 111 | 0x6F | Où vais-je? | 10177 | Potion: speed (normal) |
| 112 | 0x70 | Laissez moi partir | 10251 | Potion: paralysis (confused) |
| 113 | 0x71 | Respirez mieux | 10265 | Potion: haste (cures paralysis) |
| 114 | 0x72 | Coeur bat | 10259 | Potion: paralysis |
| 115 | 0x73 | Plus habile | 10304 | Potion: experience |
| 116 | 0x74 | Comment la renommez? | 9439 | Rename prompt (type 2) |
| 117 | 0x75 | Vous avez trouvé | 7266 | Item pickup |
| 118 | 0x76 | Vous laissez | 7661 | Drop item |
| 119 | 0x77 | Déjà identifié | 7719 | Already identified |
| 120 | 0x78 | Déjà à la main | 7865 | Already wielded |
| 122 | 0x7A | Portez maintenant | 7874 | Equip action |
| 123 | 0x7B | Table des scores | 5599 | High score header |
| 124 | 0x7C | Vous désirez: | 12622 | Menu prompt |
| 125 | 0x7D | votre choix: | 12631 | Menu choice |
| 142 | 0x8E | Vous avez gagné | 5809 | Victory display |
| 145 | 0x91 | Bienvenue au niveau | 5989 | Level up message |
| 147 | 0x93 | C'est Sauron! | 6291 | Sauron confuse attack |
| 148 | 0x94 | Armure rouille | 6069, 6091 | Shield rust |
| 149 | 0x95 | Sentez affaibli | 6544 | Constitution drain |
| 150 | 0x96 | On vous taxe | 6624 | Gold stolen (blind) |
| 151 | 0x97 | Il vous a taxé | 6621 | Gold stolen (can see) |
| 152 | 0x98 | Loupez monstre | 6801, 9343 | Miss monster |
| 153 | 0x99 | Voilà qui m'étonnerait | 3494 | Character display |
| 156 | 0x9C | Vous avez enfilé | 8487 | Ring equipped |
| 157 | 0x9D | Lequel? | 8532 | Ring selection |
| 158 | 0x9E | Avec quelle baguette? | 10693 | Wand use prompt |
| 159 | 0x9F | Quelle direction? | 8587 | Direction prompt |
| 160 | 0xA0 | Prenez une bûche | 12103 | Fall/damage |
| 172 | 0xAC | Hips! Oh, pardon | 10352 | Potion: drunk (food < 400) |
| 173 | 0xAD | Ça fait du bien | 10355 | Potion: food (food ≥ 400) |
| 175 | 0xAF | Vous avez maintenant | 7870 | Equip: weapon type 7 |
| 177 | 0xB1 | Bouger de nouveau | 12507 | Paralysis expired |
| 178 | 0xB2 | Objet lancer? | 10690 | Throw item prompt |
| 179 | 0xB3 | Tapez sur quelque chose | 6814 | Combat: hit wall/object |
| 180 | 0xB4 | Ça va mieux | 12564 | Haste expired |
| 181 | 0xB5 | Vous avez tué | 6167 | Monster kill message |
| 182 | 0xB6 | Tableau de chasse | 5355 | Kill list header |
| 183 | 0xB7 | Nourriture | 7830 | Found food |
| 184 | 0xB8 | Vous portiez | 8302 | Unequip message |
| 187 | 0xBB | Vous n'avez rien | 9313 | Error: nothing |
| 189 | 0xBD | Vous avez atteint | 4828 | Inventory display |
| 192 | 0xC0 | -- encore -- | 1194 | Pagination: more |
| 193 | 0xC1 | (* pour la liste) | 10713 | Inventory hint |
| 194 | 0xC2 | Désirez vraiment | 5907 | Confirmation prompt |
| 197 | 0xC5 | Pouâh! Horreur! | 8341 | Eat: bad food |
| 199 | 0xC7 | Votre bras s'alourdit | 6515 | Strength drain |
| 205 | 0xCD | Sentez plus bête | 6558 | Intelligence drain |
| 301 | 0x12D | Pas d'objet de ce nom | 10766 | Search: not found |
| 302 | 0x12E | Rien d'intéressant lire | 10806 | Read: nothing useful |
| 303 | 0x12F | Armure éclat argenté | 9580 | Scroll: enchant armor |
| 304 | 0x130 | Parchemin fumée | 9767 | Scroll: poof |
| 305 | 0x131 | Très bon magicien | 10822 | Scroll: requires skill |
| 306 | 0x132 | Plus fort. Quels muscles | 10143 | Potion: stamina (normal) |
| 307 | 0x133 | Super pied, ce bled | 10282 | Potion: hallucination |
| 327 | 0x147 | Armure ensorcellée | 8224, 8264 | Error: cursed armor/ring |
| 328 | 0x148 | Trop chargé | 10883 | Error: overweight |
| 329 | 0x149 | MORIA Version 1.9.8.7 | 12620 | Title screen |
| 330 | 0x14A | Fichier MORIA.TXT absent | 5316 | Error: missing file |
| 331 | 0x14B | Sens de l'orientation | 12097 | Scroll: map reveal |
| 403 | 0x193 | ration | 4447 | Object info: food |
| 404 | 0x194 | alimentaire | 4449 | Object info: food adj |
| 405 | 0x195 | (en service) | 4801 | Equipment: active |
| 406 | 0x196 | potion | 4651 | Object: potion label |
| 407 | 0x197 | parchemin | 4654 | Object: scroll label |
| 408 | 0x198 | renommé | 4696 | Item: renamed tag |
| 409 | 0x199 | intitulé | 4724 | Item: titled tag |
| 410 | 0x19A | un anneau | 4456 | Object: ring label |
| 411 | 0x19B | renommé | 4469 | Ring: renamed |
| 412 | 0x19C | une baguette | 4544 | Object: wand label |
| 413 | 0x19D | renommée | 4556 | Wand: renamed |
| 414 | 0x19E | Un Silmaril | 4606 | Object: Silmaril |
| 415 | 0x19F | pièces d'or | 4602, 5833 | Gold display |
| 416 | 0x1A0 | en finir ? | 5910 | Suicide confirm |
| 417 | 0x1A1 | terminer ? | 5913 | Quit confirm |
| 418 | 0x1A2 | Version 4.1.1 | 3867 | Death screen version |
| 419 | 0x1A3 | Quel Dommage ! | 5835 | What a pity! |
| 420 | 0x1A4 | vous a volé | 6684 | Monster stole from you |
| 421 | 0x1A5 | Vous aviez | 8558 | Belt item removed |
| 424 | 0x1A8 | des gantelets | 4754 | Object: gauntlets |

### Dynamic Message ID Patterns

Some calls use computed IDs:

| Pattern | Line(s) | Description |
|---------|---------|-------------|
| `flag + 0x2A` | 3465 | Intro messages (IDs 42–45 for flag 0–3) |
| `value + 0x87` | 1985 | Ability display: ring slave variants (IDs 135+) |
| `value + 0x7E` | 2007 | Death type messages (IDs 126+) |
| `value + 0x7E + value` | 2003 | Double-offset death messages |
| `food/100 + 0x30` | 8350 | Food quality messages (IDs 48–59) |
| `iVar9 + 0xD` | 9771 | Random scroll effects (IDs 13–19) |
| `local_5 + 0x34` | 12626 | Main menu options (IDs 52–55) |
| `iVar9 + 0x1A6` | 11996 | Fall messages (IDs 422–423) |

---

## Summary Statistics

| Category | Count |
|----------|-------|
| Region 1 messages (IDs 1–91) | 91 |
| Region 2 messages (IDs 101–210) | 110 |
| Region 3 messages (IDs 301–332+) | ~32 |
| Region 4 labels (IDs 401–425) | 25 |
| Item descriptions | 131 |
| Potion colors | 24 |
| Ring materials | 19 |
| Wand woods | 22 |
| Gem types | 10 |
| **Total strings extracted** | **~549** |
| `display_score_with_fatal` calls in C | **~195** |
