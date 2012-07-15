/**
 * string file porter2_stemmer.cpp
 */

#include <boost/regex.hpp>
#include "porter2_stemmer.h"

using namespace Porter2Stemmer::internal;
using std::string;
using boost::regex;
using boost::smatch;

#include <iostream>
using std::cout;
using std::endl;

string Porter2Stemmer::stem(const string & toStem)
{
    string word = prepareWord(toStem);

    if(returnImmediately(word))
        return finalStem(word);

    changeY(word);
    int startR1 = getStartR1(word);
    int startR2 = getStartR2(word, startR1);
    removeApostrophe(word);
    step1A(word);
    step1B(word, startR1);
    step1C(word);
    step2(word, startR1);
    step3(word, startR1, startR2);
    step4(word, startR2);
    step5(word, startR1, startR2);

    return finalStem(word);
}

string Porter2Stemmer::internal::finalStem(string & word)
{
    word = regex_replace(word, regex("Y"), "y");
    word = regex_replace(word, regex("'"), "");
    return word;
}

string Porter2Stemmer::internal::prepareWord(const string & toStem)
{
    string word = "";
    for(auto ch: toStem)
    {
        if(ch > 'A' && ch < 'Z')
            ch += 32;
        if((ch > 'a' && ch < 'z') || ch == '\'')
            word += ch;
    }
    return word;
}

bool Porter2Stemmer::internal::returnImmediately(const string & word)
{
    return word.size() <= 2;
}

int Porter2Stemmer::internal::getStartR1(const string & word)
{
    smatch results;
    if(regex_search(word, results, regex("[aeiouy][^aeiouy]")))
        return results.position() + 2;
    else
        return word.size();
}

int Porter2Stemmer::internal::getStartR2(const string & word, int startR1)
{
    if(startR1 == word.size())
        return startR1;

    string split = word.substr(startR1, word.size() - startR1);

    smatch results;
    if(regex_search(split, results, regex("[aeiouy][^aeiouy]")))
        return results.position() + startR1 + 2;
    else
        return word.size();
}

void Porter2Stemmer::internal::changeY(string & word)
{
    if(word.find_first_of("y") == string::npos)
        return;

    if(word[0] == 'y')
        word[0] = 'Y';

    word = regex_replace(word, regex("([aeiou])y"), "$1Y");
}

void Porter2Stemmer::internal::removeApostrophe(string & word)
{
    smatch results;
    word = regex_replace(word, regex("'s.*$"), "");
}

void Porter2Stemmer::internal::step1A(string & word)
{
    smatch results;
    if(regex_search(word, results, regex("sses$")))
    {
        regex_replace(word, regex("(.*)sses$"), "$1ss");
        return;
    }

    if(regex_search(word, results, regex(".*(ied|ies)")))
    {
        if(results.position() > 1)
        {
            regex_replace(word, regex(".*(ied|ies)$"), "$1i");
            return;
        }
    }
    else
    {
        regex_replace(word, regex(".*(ied|ies)$"), "$1ie");
        return;
    }

    if(regex_search(word, results, regex(".*(u|s)s$")))
        return;

    if(regex_search(word, results, regex(".*[aeiouy](.*)+s$")))
        word = word.substr(0, word.size() - 1);
}

void Porter2Stemmer::internal::step1B(string & word, int startR1)
{
  //if word.search(/(eed|eedly)$/) >= startR1
  //return word.replace(/(\w*)(eed|eedly)/, "$1ee")
  //if word.match(/\w*?[aeiouy]\w+(ed|edly|ing|ingly)$/)
  //word = word.match(/^(\w*?[aeiouy]\w+)(ed|edly|ing|ingly)$/)[1]
  //return word + "e" if word.match(/(at|bl|iz)$/)
  //if word.match(/(bb|dd|ff|gg|mm|nn|pp|rr|tt)$/)
  //return word.slice(0, word.length - 1)
  //return word + "e" if string isShort(word, startR1)
}

void Porter2Stemmer::internal::step1C(string & word)
{
    word = regex_replace(word, regex("(.+[^aeiouy])(y|Y)$"), "$1i");
}

void Porter2Stemmer::internal::step2(string & word, int startR1)
{
  //if word.search(/ational$/) >= startR1
  //return word.replace /(\w*)ational$/, "$1ate"
  //if word.search(/tional$/) >= startR1
  //return word.replace /(\w*)tional$/, "$1tion"
  //if word.search(/ization$/) >= startR1
  //return word.replace /(\w*)ization$/, "$1ize"
  //if word.search(/(ation|ator)$/) >= startR1
  //return word.replace /(\w*)(ation|ator)$/, "$1ate"
  //if word.search(/(alism|aliti|alli)$/) >= startR1
  //return word.replace /(\w*)(alism|aliti|alli)$/, "$1al"
  //if word.search(/enci$/) >= startR1
  //return word.replace /(\w*)enci$/, "$1ence"
  //if word.search(/anci$/) >= startR1
  //return word.replace /(\w*)anci$/, "$1ance"
  //if word.search(/abli$/) >= startR1
  //return word.replace /(\w*)abli$/, "$1able"
  //if word.search(/entli$/) >= startR1
  //return word.replace /(\w*)entli$/, "$1ent"
  //if word.search(/fulness$/) >= startR1
  //return word.replace /(\w*)fulness$/, "$1ful"
  //if word.search(/(ousli|ousness)$/) >= startR1
  //return word.replace /(\w*)(ousli|ousness)$/, "$1ous"
  //if word.search(/(iveness|iviti)$/) >= startR1
  //return word.replace /(\w*)(iveness|iviti)$/, "$1ive"
  //if word.search(/(biliti|bli)$/) >= startR1
  //return word.replace /(\w*)(biliti|bli)$/, "$1ble"
  //if word.search(/logi$/) >= startR1
  //return word.replace /(\w*l)ogi$/, "$1og"
  //if word.search(/fulli$/) >= startR1
  //return word.replace /(\w*)fulli$/, "$1ful"
  //if word.search(/lessli$/) >= startR1
  //return word.replace /(\w*)lessli$/, "$1less"
  //if word.search(/[cdeghkmnrt]li$/) >= startR1
  //return word.replace /(\w*)li$/, "$1"
}

void Porter2Stemmer::internal::step3(string & word, int startR1, int startR2)
{
  //if word.search(/ational$/) >= startR1
  //return word.replace /(\w*)ational$/, "$1ate"
  //if word.search(/tional$/) >= startR1
  //return word.replace /(\w*)tional$/, "$1tion"
  //if word.search(/alize$/) >= startR1
  //return word.replace /(\w*)alize$/, "$1al"
  //if word.search(/(icate|iciti|ical)$/) >= startR1
  //return word.replace /(\w*)(icate|iciti|ical)$/, "$1ic"
  //if word.search(/(ful|ness)$/) >= startR1
  //return word.replace /(\w*)(ful|ness)$/, "$1"
  //if word.search(/ative$/) >= startR2
  //return word.replace /(\w*)ative$/, "$1"
}

void Porter2Stemmer::internal::step4(string & word, int startR2)
{
  //if word.search(/ement$/) >= startR2
  //return word.replace /(\w*)ement$/, "$1"
  //if word.search(/ment$/) >= startR2
  //return word.replace /(\w*)ment$/, "$1"
  //if word.search(/(al|ance|ence|er|ic|able|ible|ant|ent|ism|ate|iti|ous|ive|ize)$/) >= startR2
  //return word.replace /(\w*)(al|ance|ence|er|ic|able|ible|ant|ent|ism|ate|iti|ous|ive|ize)$/, "$1"
  //if word.search(/(s|t)ion$/) >= startR2
  //return word.replace /(\w*)(s|t)ion$/, "$1"
}

void Porter2Stemmer::internal::step5(string & word, int startR1, int startR2)
{
  //if word.search(/e$/) >= startR2
  //return word.slice(0, word.length - 1)
  //if word.search(/e$/) >= startR1 and (not string isShort(word.match(/(\w*)e$/)[1], startR1))
  //return word.slice(0, word.length - 1)
  //if word.search(/ll$/) >= startR2
  //return word.slice(0, word.length - 1)
}

bool Porter2Stemmer::internal::isShort(const string & word, int startR1)
{
    //word.match(/^([aeouiy][^aeouiy]|\w*[^aeiouy][aeouiy][^aeouiyYwx])$/) != null and startR1 >= word.length
    return false;
}
