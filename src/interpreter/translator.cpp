/*
	Copyright (C) 2003-2006 Cies Breijs <cies # kde ! nl>

	This program is free software; you can redistribute it and/or
	modify it under the terms of version 2 of the GNU General Public
	License as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public
	License along with this program; if not, write to the Free
	Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
	Boston, MA 02110-1301, USA.
*/

#include <QDomDocument>
#include <QFile>

#include <QtDebug>


#include "token.h"

#include "translator.h"



Translator* Translator::m_instance = 0;  // initialize pointer

Translator* Translator::instance()
{
	if (m_instance == 0) m_instance = new Translator;  // create sole instance if its the first call
	return m_instance;  // address of sole instance
}

Translator::Translator()
	: localizer(0), currentLangugeCode("")
{
}

Translator::~Translator()
{
	delete m_instance;
	m_instance = 0;
}


int Translator::look2type(QString& look)
{
	if (look2typeMap.contains(look))
		return look2typeMap[look];
	return Token::Unknown;
}

int Translator::look2type(QChar& look)
{
	if (look2typeMap.contains(static_cast<QString>(look)))
		return look2typeMap[static_cast<QString>(look)];
	return Token::Unknown;
}

QList<QString> Translator::type2look(int type)
{
	return look2typeMap.keys(type);
}

QHash<int, QList<QString> > Translator::token2stringsMap()
{
	QHash<int, QList<QString> > resultMap;
	QList<int> tokenList = look2typeMap.values();
	foreach (int token, tokenList) resultMap.insert(token, look2typeMap.keys(token));
	return resultMap;
}


bool Translator::setLanguage(const QString &lang_code)
{
	if (currentLangugeCode == lang_code) return true;

	if (localizer != 0) delete localizer;

// 	if (KGlobal::locale()->language() == lang_code)  // re-use the global localizer TODO maked shure not to delete it!
// 		localizer = KGlobal::locale();
// 	else

	localizer = new KLocale(lang_code);

	if (localizer->language() != lang_code) return false;  // the GUI needs to give feedback if it didn't work

	currentLangugeCode = lang_code;

	setDictionary();
	setExamples();

	return true;
}


void Translator::setDictionary()
{
	look2typeMap.clear();
	default2localizedMap.clear();

	QString localizedCommandLook;


//BEGIN GENERATED translator_cpp CODE

/* The code between the line that start with "//BEGIN GENERATED" and "//END GENERATED"
 * is generated by "generate.rb" according to the definitions specified in
 * "definitions.rb". Please make all changes in the "definitions.rb" file, since all
 * all change you make here will be overwritten the next time "generate.rb" is run.
 * Thanks for looking at the code!
 */

	look2typeMap["$"] = Token::VariablePrefix;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'True' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"true").toString(localizer);
	default2localizedMap["true"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::True;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'False' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"false").toString(localizer);
	default2localizedMap["false"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::False;

	look2typeMap["#"] = Token::Comment;

	look2typeMap["\""] = Token::StringDelimiter;

	look2typeMap["{"] = Token::ScopeOpen;

	look2typeMap["}"] = Token::ScopeClose;

	look2typeMap["("] = Token::ParenthesisOpen;

	look2typeMap[")"] = Token::ParenthesisClose;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'ArgumentSeparator' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		",").toString(localizer);
	default2localizedMap[","] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::ArgumentSeparator;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'DecimalSeparator' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		".").toString(localizer);
	default2localizedMap["."] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::DecimalSeparator;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Exit' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"exit").toString(localizer);
	default2localizedMap["exit"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Exit;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'If' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"if").toString(localizer);
	default2localizedMap["if"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::If;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Else' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"else").toString(localizer);
	default2localizedMap["else"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Else;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Repeat' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"repeat").toString(localizer);
	default2localizedMap["repeat"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Repeat;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'While' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"while").toString(localizer);
	default2localizedMap["while"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::While;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'For' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"for").toString(localizer);
	default2localizedMap["for"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::For;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'To' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"to").toString(localizer);
	default2localizedMap["to"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::To;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Step' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"step").toString(localizer);
	default2localizedMap["step"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Step;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Break' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"break").toString(localizer);
	default2localizedMap["break"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Break;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Return' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"return").toString(localizer);
	default2localizedMap["return"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Return;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Wait' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"wait").toString(localizer);
	default2localizedMap["wait"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Wait;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'And' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"and").toString(localizer);
	default2localizedMap["and"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::And;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Or' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"or").toString(localizer);
	default2localizedMap["or"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Or;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Not' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"not").toString(localizer);
	default2localizedMap["not"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Not;

	look2typeMap["=="] = Token::Equals;

	look2typeMap["!="] = Token::NotEquals;

	look2typeMap[">"] = Token::GreaterThan;

	look2typeMap["<"] = Token::LessThan;

	look2typeMap[">="] = Token::GreaterOrEquals;

	look2typeMap["<="] = Token::LessOrEquals;

	look2typeMap["+"] = Token::Addition;

	look2typeMap["-"] = Token::Substracton;

	look2typeMap["*"] = Token::Multiplication;

	look2typeMap["/"] = Token::Division;

	look2typeMap["^"] = Token::Power;

	look2typeMap["="] = Token::Assign;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Learn' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"learn").toString(localizer);
	default2localizedMap["learn"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Learn;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Reset' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"reset").toString(localizer);
	default2localizedMap["reset"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Reset;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Clear' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"clear").toString(localizer);
	default2localizedMap["clear"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Clear;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Center' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"center").toString(localizer);
	default2localizedMap["center"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Center;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Go' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"go").toString(localizer);
	default2localizedMap["go"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Go;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GoX' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"gox").toString(localizer);
	default2localizedMap["gox"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GoX;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'GoY' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"goy").toString(localizer);
	default2localizedMap["goy"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::GoY;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Forward' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"forward").toString(localizer);
	default2localizedMap["forward"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Forward;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Backward' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"backward").toString(localizer);
	default2localizedMap["backward"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Backward;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Direction' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"direction").toString(localizer);
	default2localizedMap["direction"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Direction;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'TurnLeft' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"turnleft").toString(localizer);
	default2localizedMap["turnleft"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::TurnLeft;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'TurnRight' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"turnright").toString(localizer);
	default2localizedMap["turnright"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::TurnRight;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenWidth' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"penwidth").toString(localizer);
	default2localizedMap["penwidth"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenWidth;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenUp' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"penup").toString(localizer);
	default2localizedMap["penup"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenUp;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenDown' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pendown").toString(localizer);
	default2localizedMap["pendown"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenDown;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'PenColor' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"pencolor").toString(localizer);
	default2localizedMap["pencolor"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::PenColor;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'CanvasColor' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"canvascolor").toString(localizer);
	default2localizedMap["canvascolor"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::CanvasColor;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'CanvasSize' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"canvassize").toString(localizer);
	default2localizedMap["canvassize"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::CanvasSize;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'SpriteShow' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"spriteshow").toString(localizer);
	default2localizedMap["spriteshow"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::SpriteShow;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'SpriteHide' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"spritehide").toString(localizer);
	default2localizedMap["spritehide"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::SpriteHide;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Print' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"print").toString(localizer);
	default2localizedMap["print"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Print;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'FontSize' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"fontsize").toString(localizer);
	default2localizedMap["fontsize"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::FontSize;

	localizedCommandLook = ki18nc(
		"You are about to translate the 'Random' COMMAND, there are some rules on how to translate it."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
		"random").toString(localizer);
	default2localizedMap["random"] = localizedCommandLook;
	look2typeMap[localizedCommandLook] = Token::Random;


//END GENERATED translator_cpp CODE

}



void Translator::setExamples()
{
	examples.clear();
	QString exampleName;

	exampleName = ki18nc(
		"This is an EXAMPLE NAME in KTurtle."
		"Please see http://edu.kde.org/kturtle/translator.php to learn know how to properly translate it.",
		"triangle").toString(localizer);
	examples[exampleName] = parseExampleTranslations(ki18nc(
		"You are about to translate the 'triangle' EXAMPLE PROGRAM, examples have to be translated in a speacial way."
		"Please see http://edu.kde.org/kturtle/translator.php to learn how to properly translate it.",
				"# Example: %1\n"
				"\n"
				"@(repeat) 3 {\n"
				"  @(forward) 100\n"
				"  @(turnleft) 120\n"
				"}\n"
		).subs(exampleName).toString(localizer));

	exampleName = ki18nc(
		"This is an EXAMPLE NAME in KTurtle."
		"Please see http://edu.kde.org/kturtle/translator.php to learn know how to properly translate it.",
		"curly").toString(localizer);
	examples[exampleName] = parseExampleTranslations(ki18nc(
		"You are about to translate the 'curly' EXAMPLE PROGRAM, examples have to be translated in a speacial way."
		"Please see http://edu.kde.org/kturtle/translator.php to learn know how to properly translate it.",
				"# Example: %1\n"
				"# This example draws some nice curving shapes...\n"
				"\n"
				"@(reset)\n"
				"@(penup)\n"
				"@(forward) 50\n"
				"@(pendown)\n"
				"\n"
				"@(repeat) 4 {\n"
				"  @(for) $x = 1 @(to) 100 {\n"
				"    @(forward) 10\n"
				"    @(turnright) 100 - $x\n"
				"  }\n"
				"}\n"
		).subs(exampleName).toString(localizer));
}

QString Translator::parseExampleTranslations(const QString& halfTranslatedExample)
{
	QString result = halfTranslatedExample;
	Translator* translator = Translator::instance();
	QRegExp rx("@\\(.*\\)");
	rx.setMinimal(true);  // make it not greedy

	int pos = 0;
	while ((pos = rx.indexIn(result, pos)) != -1) {
		QString original = result.mid(pos, rx.matchedLength());
		original = original.mid(2, original.length() - 3);
		result = result.replace(pos, rx.matchedLength(), translator->default2localized(original));
	}

	return result;
}
