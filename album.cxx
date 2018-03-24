#encoding "utf-8"
#GRAMMAR_ROOT S

NP -> Noun;
NP -> Adj<nc-agr[1]> NP<nc-agr[1], rt>;
NP -> NP<nc-agr[1]> Adj<nc-agr[1]>;

// название альбома
Title -> Word<h-reg1, quoted>;
Title -> Word<h-reg1, l-quoted, ~r-quoted> Word<~l-quoted, r-quoted>;
Title -> Word<h-reg1, l-quoted, ~r-quoted> AnyWord<~r-quoted>+ Word<~l-quoted, r-quoted>;

TitleWQ -> Word<h-reg1> Word<h-reg1>*;
TitleWQ -> Word<h-reg1>+ AnyWord Word<h-reg1>;

AlbumTitle -> Title<fw> interp(Album.Name::not_norm);
AlbumTitle -> TitleWQ<fw> interp(Album.Name::not_norm);

// группа/исполнитель
Name -> Word<h-reg1, ~fw> Word<h-reg1>*; 
SingerPref -> 'альбом' | 'группа'<gram="род"> | 'музыкант'<gram="род"> | 'певица'<gram="род"> | 'рэпер'<gram="род">;
Singer -> SingerPref NP* Name interp (Album.Singer);

// перевод названия альбома
TranslateTitle -> Title | TitleWQ | Word<h-reg1>+ AnyWord;
Lang -> "англ" | "рус" | "англ." | "рус.";
Translate -> LBracket Word* Lang Hyphen* TranslateTitle interp (Album.TranslateName::not_norm) RBracket;

S -> AlbumTitle (Translate) Hyphen AnyWord* Singer;

// дата релиза
Date -> AnyWord<kwtype="даты">;
Premiere -> "выйти" | "выпустить" | "издать" "в" | "записать" | "состояться";
S -> Premiere (Word) Date interp (Album.Date::not_norm);
