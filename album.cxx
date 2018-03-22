#encoding "utf-8"
#GRAMMAR_ROOT S

NP -> Noun;
NP -> Adj<nc-agr[1]> NP<nc-agr[1], rt>;
NP -> NP<nc-agr[1]> Adj<nc-agr[1]>;

//Даты
Date -> AnyWord<kwtype="даты">;

Title -> Word<h-reg1, quoted>;
Title -> Word<h-reg1, l-quoted, ~r-quoted> Word<~l-quoted, r-quoted>;
Title -> Word<h-reg1, l-quoted, ~r-quoted> AnyWord<~r-quoted>+ Word<~l-quoted, r-quoted>;

TitleWQ -> Word<h-reg1> Word<h-reg1>*;
TitleWQ -> Word<h-reg1>+ AnyWord Word<h-reg1>;

// OriginalTitle -> Word Hyphen* LBracket Word* RBracket Hyphen* Word interp (Album.OriginalName);

InBrackets -> LBracket Word* RBracket;

AlbumTitle -> Title<fw> interp(Album.Name::not_norm);
AlbumTitle -> TitleWQ<fw> interp(Album.Name::not_norm);

Premiere -> "выйти" | "выпустить" | "издать" "в" | "записать" | "состояться";
PostW -> "год"<gram="род"> ;//| "экземпляр";
S -> Premiere (Word) Date interp (Album.Date::not_norm);

Name -> Word<h-reg1, ~fw> Word<h-reg1>*; 
SingerPref -> 'альбом' | 'группа'<gram="род"> | 'музыкант'<gram="род"> | 'певица'<gram="род"> | 'рэпер'<gram="род">;
Singer -> SingerPref NP* Name interp (Album.Singer);

TranslateTitle -> Title | TitleWQ | Word<h-reg1>+ AnyWord;
Lang -> "англ" | "рус" | "англ." | "рус.";
Translate -> LBracket Word* Lang Hyphen* TranslateTitle interp (Album.TranslateName::not_norm) RBracket;

//S -> AlbumTitle Hyphen* (Date interp (Album.Date::not_norm)) Singer;
//S -> AlbumTitle (Singer);
//S -> AlbumTitle Hyphen* Word* Singer;
//S -> AlbumTitle InBrackets Hyphen* Word* Singer;
//S -> Singer;
S -> AlbumTitle (Translate) Hyphen AnyWord* Singer;
