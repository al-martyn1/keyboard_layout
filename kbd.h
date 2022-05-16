#pragma once


#include <string>
#include <vector>
#include <utility>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/style
// https://developer.mozilla.org/ru/docs/Web/SVG/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82/%3Ctext%3E
// https://developer.mozilla.org/ru/docs/Web/SVG/%D0%AD%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82/rect
// https://stackoverflow.com/questions/10768451/inline-svg-in-css



const char *svgBegin = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n\
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\
    \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\
<svg version=\"1.1\"\n\
     baseProfile=\"full\"\n\
     xmlns=\"http://www.w3.org/2000/svg\"\n\
     xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n\
     xmlns:ev=\"http://www.w3.org/2001/xml-events\"\n\
     width=\"100%\" height=\"100%\">\n\
     <style>\n\
         .key_label    { font: 600 9pt sans-serif; }\n\
         .key_label_sm { font: 600 6pt  sans-serif; }\n\
     </style>\n\
";

// font: bold vs font: 500
const char *svgEnd = "</svg>";




inline
std::vector<std::string> split( const std::string &str, char delim, bool skipEmpty = true )
{
    std::istringstream tokenStream(str);
    
    std::vector<std::string> tokens;

    std::string s;

    while( std::getline( tokenStream, s, delim ) )
    {
        if (s.empty() && skipEmpty)
            continue;
        tokens.push_back(s);
    }

    return tokens;
}





struct SvgRect
{
    int   xPos;
    int   yPos;
    int   width;
    int   height;
    int   rx;
    int   ry;
    std::string fillColor;
    std::string strokeColor;
    //std::string strokeWidth;
    int strokeWidth;

    // C++ 0x03
    SvgRect( int xp, int yp, int w, int h, int _rx, int _ry, const std::string &fc, const std::string &sc, int sw )
    : xPos(xp)
    , yPos(yp)
    , width(w)
    , height(h)
    , rx(_rx)
    , ry(_ry)
    , fillColor(fc)
    , strokeColor(sc)
    , strokeWidth(sw)
    {}

};

inline
std::ostream& operator<<( std::ostream& os, const SvgRect &r )
{
    os<<"<rect ";
    os<<"x=\""<<r.xPos<<"\" ";
    os<<"y=\""<<r.yPos<<"\" ";
    os<<"width=\""<<r.width<<"\" ";
    os<<"height=\""<<r.height<<"\" ";
    os<<"rx=\""<<r.rx<<"\" ";
    os<<"ry=\""<<r.ry<<"\" ";
    os<<"fill=\""<<r.fillColor<<"\" ";
    os<<"stroke=\""<<r.strokeColor<<"\" ";
    os<<"stroke-width=\""<<r.strokeWidth<<"\" ";
    os<<"/>";

    return os;
}

struct SvgTransparentRect
{
    int   xPos;
    int   yPos;
    int   width;
    int   height;
    int   rx;
    int   ry;
    std::string strokeColor;
    int strokeWidth;

    // C++ 0x03
    SvgTransparentRect( int xp, int yp, int w, int h, int _rx, int _ry, const std::string &sc, int sw )
    : xPos(xp)
    , yPos(yp)
    , width(w)
    , height(h)
    , rx(_rx)
    , ry(_ry)
    , strokeColor(sc)
    , strokeWidth(sw)
    {}

};

inline
std::ostream& operator<<( std::ostream& os, const SvgTransparentRect &r )
{
    os<<"<rect ";
    os<<"x=\""<<r.xPos<<"\" ";
    os<<"y=\""<<r.yPos<<"\" ";
    os<<"width=\""<<r.width<<"\" ";
    os<<"height=\""<<r.height<<"\" ";
    os<<"rx=\""<<r.rx<<"\" ";
    os<<"ry=\""<<r.ry<<"\" ";
    os<<"style=\"fill-opacity: .0;\" ";
    os<<"stroke=\""<<r.strokeColor<<"\" ";
    os<<"stroke-width=\""<<r.strokeWidth<<"\" ";
    os<<"/>";

    return os;
}


struct SvgGenericKeyboardButton
{
    int   xPos;
    int   yPos;
    int   width;
    int   height;
    std::string fillColor;
    std::string strokeColor;

    SvgGenericKeyboardButton( int xp, int yp, int w, int h, const std::string &fc, const std::string &sc )
    : xPos(xp)
    , yPos(yp)
    , width(w)
    , height(h)
    , fillColor(fc)
    , strokeColor(sc)
    {}

};

inline
std::ostream& operator<<( std::ostream& os, const SvgGenericKeyboardButton &b )
{
    os<<SvgRect( b.xPos, b.yPos, b.width, b.height, defKeyboardButtonRoundingX, defKeyboardButtonRoundingY, b.fillColor, b.strokeColor, defKeyboardButtonStrokeThickness );
    return os;
}


struct SvgKeyboardButton
{
    int     xPos;
    int     yPos;
    double  wScale;
    double  hScale;
    std::string fillColor;
    std::string strokeColor;

    SvgKeyboardButton( int xp, int yp, double wsc, double hsc, const std::string &fc, const std::string &sc )
    : xPos(xp)
    , yPos(yp)
    , wScale(wsc)
    , hScale(hsc)
    , fillColor(fc)
    , strokeColor(sc)
    {}

};

inline
std::ostream& operator<<( std::ostream& os, const SvgKeyboardButton &b )
{
    os<<SvgGenericKeyboardButton(b.xPos, b.yPos, (int)(defKeyboardButtonHeight*b.wScale), (int)(defKeyboardButtonHeight*b.hScale), b.fillColor, b.strokeColor )<<"\n";
    return os;
}

inline
std::string xmlEscape( const std::string &s )
{
    std::string res;
    std::string::size_type i = 0, size = s.size();
    for(; i!=size; ++i)
    {
        char ch = s[i];
        if (ch=='&')
            res.append("&amp;");
        else if (ch=='\'')
            res.append("&apos;");
        else if (ch=='\"')
            res.append("&quot;");
        else if (ch=='<')
            res.append("&lt;");
        else if (ch=='>')
            res.append("&gt;");
        else
            res.append(1, ch);
    }

    return res;
}

struct SvgText
{
    int          xPos;
    int          yPos;
    std::string  text;
    std::string  color;
    std::string  className;

    SvgText( int xp, int yp, const std::string &txt, const std::string &clr = "", const std::string &cls = "" )
    : xPos(xp)
    , yPos(yp)
    , text(txt)
    , color(clr)
    , className(cls)
    {}

    //fill: #6dd
};

inline
std::ostream& operator<<( std::ostream& os, const SvgText &t )
{
    os<<"<text ";
    os<<"x=\""<<t.xPos<<"\" ";
    os<<"y=\""<<t.yPos<<"\" ";

    if (!t.className.empty())
        os<<"class=\""<<t.className<<"\" ";
    else
        os<<"class=\"key_label\" ";

    if (!t.color.empty())
        os<<"style=\"fill: "<<t.color<<";\" ";

    os<<">";
    os<<xmlEscape(t.text);

    os<<"</text>";

    return os;
}

/*
struct SvgKeyboardButtonTexts
{
    std::string lt;
    std::string rt;
    std::string lb;
    std::string rb;

    SvgKeyboardButtonTexts( const std::string &_lt
                          , const std::string &_rt
                          , const std::string &_lb
                          , const std::string &_rb
                          )
    : lt(_lt)
    , rt(_rt)
    , lb(_lb)
    , rb(_rb)
    {}

};
*/

struct SvgKeyboardButtonText
{
    std::string text;
    std::string color;

    SvgKeyboardButtonText( const std::string &t = "", const std::string &c = "black") : text(t), color(c) { }
    SvgKeyboardButtonText( const SvgKeyboardButtonText &t) : text(t.text), color(t.color) { }

};

template<typename ItemType>
inline
std::vector<ItemType>& push_back_helper( std::vector<ItemType> &v, const ItemType &elem )
{
    v.push_back(elem);
    return v;
}


inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonTexts( const std::string &color, size_t cnt )
{
    std::vector<SvgKeyboardButtonText> res;
    while(cnt--)
        res.push_back( SvgKeyboardButtonText(std::string(), color) );
}

inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonTexts( const std::string &color, const std::string &t1 )
{
    return push_back_helper( std::vector<SvgKeyboardButtonText>(), SvgKeyboardButtonText(t1, color) );
}

inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonTexts( const std::string &color, const std::string &t1, const std::string &t2 )
{
    return push_back_helper( makeSvgKeyboardButtonTexts(color, t1), SvgKeyboardButtonText(t2, color) );
}

inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonTexts( const std::string &color, const std::string &t1, const std::string &t2, const std::string &t3 )
{
    return push_back_helper( makeSvgKeyboardButtonTexts(color, t1, t2), SvgKeyboardButtonText(t3, color) );
}

inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonTexts( const std::string &color, const std::string &t1, const std::string &t2, const std::string &t3, const std::string &t4 )
{
    return push_back_helper( makeSvgKeyboardButtonTexts(color, t1, t2, t3), SvgKeyboardButtonText(t4, color) );
}

inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonTexts( const std::vector<SvgKeyboardButtonText> &v1, const std::vector<SvgKeyboardButtonText> &v2 )
{
    std::vector<SvgKeyboardButtonText> res = v1;
    res.insert( res.end(), v2.begin(), v2.end() );
    return res;
}
/*
struct SvgKeyboardButtonText
{
    std::string text;
    std::string color;
*/

inline
std::vector<SvgKeyboardButtonText> normalizeLabels( const std::vector<SvgKeyboardButtonText> &labels )
{
    if (labels.empty())
        return labels;

    size_t nonEmptyLabelsCounter = 0;

    std::vector<SvgKeyboardButtonText>::const_iterator it = labels.begin();
    for(; it != labels.end(); ++it)
    {
        if (!it->text.empty())
            nonEmptyLabelsCounter++;
    }

    if (nonEmptyLabelsCounter>1)
        return labels;

    std::vector<SvgKeyboardButtonText> res;

    it = labels.begin();
    for(; it != labels.end(); ++it)
    {
        if (!it->text.empty())
        {
            res.push_back(*it);
            break;
        }
    }

    return res;
}




struct SvgKeyboardButtonWithText
{
    int     xPos;
    int     yPos;
    double  wScale;
    double  hScale;
    bool    smallFont;
    std::string fillColor;
    std::string strokeColor;

    std::vector<SvgKeyboardButtonText>  labels;

    // Two labels diff colors
    SvgKeyboardButtonWithText( int xp, int yp, double wsc, double hsc, bool small, const std::string &fc, const std::string &sc
                             , const std::string &_lt, const std::string &_ltColor
                             , const std::string &_lb, const std::string &_lbColor
                             )
    : xPos(xp)
    , yPos(yp)
    , wScale(wsc)
    , hScale(hsc)
    , smallFont(small)
    , fillColor(fc)
    , strokeColor(sc)
    {
        labels.push_back( SvgKeyboardButtonText(_lt, _ltColor) );
        labels.push_back( SvgKeyboardButtonText(_lb, _lbColor) );
    }

    // Two labels one color
    SvgKeyboardButtonWithText( int xp, int yp, double wsc, double hsc, bool small, const std::string &fc, const std::string &sc
                             , const std::string &_lt
                             , const std::string &_lb
                             , const std::string &txtColor
                             )
    : xPos(xp)
    , yPos(yp)
    , wScale(wsc)
    , hScale(hsc)
    , smallFont(small)
    , fillColor(fc)
    , strokeColor(sc)
    {
        labels.push_back( SvgKeyboardButtonText(_lt, txtColor) );
        labels.push_back( SvgKeyboardButtonText(_lb, txtColor) );
    }

    // Four labels diff colors
    SvgKeyboardButtonWithText( int xp, int yp, double wsc, double hsc, bool small, const std::string &fc, const std::string &sc
                             , const std::string &_lt, const std::string &_ltColor
                             , const std::string &_lb, const std::string &_lbColor
                             , const std::string &_rt, const std::string &_rtColor
                             , const std::string &_rb, const std::string &_rbColor
                             )
    : xPos(xp)
    , yPos(yp)
    , wScale(wsc)
    , hScale(hsc)
    , smallFont(small)
    , fillColor(fc)
    , strokeColor(sc)
    {
        labels.push_back( SvgKeyboardButtonText(_lt, _ltColor) );
        labels.push_back( SvgKeyboardButtonText(_lb, _lbColor) );
        labels.push_back( SvgKeyboardButtonText(_rt, _rtColor) );
        labels.push_back( SvgKeyboardButtonText(_rb, _rbColor) );
    }

    // Four labels one color
    SvgKeyboardButtonWithText( int xp, int yp, double wsc, double hsc, bool small, const std::string &fc, const std::string &sc
                             , const std::string &_lt
                             , const std::string &_lb
                             , const std::string &_rt
                             , const std::string &_rb
                             , const std::string &txtColor
                             )
    : xPos(xp)
    , yPos(yp)
    , wScale(wsc)
    , hScale(hsc)
    , smallFont(small)
    , fillColor(fc)
    , strokeColor(sc)
    {
        labels.push_back( SvgKeyboardButtonText(_lt, txtColor) );
        labels.push_back( SvgKeyboardButtonText(_lb, txtColor) );
        labels.push_back( SvgKeyboardButtonText(_rt, txtColor) );
        labels.push_back( SvgKeyboardButtonText(_rb, txtColor) );
    }

    // Single label
    SvgKeyboardButtonWithText( int xp, int yp, double wsc, double hsc, bool small, const std::string &fc, const std::string &sc
                             , const std::string &text
                             , const std::string &txtColor
                             )
    : xPos(xp)
    , yPos(yp)
    , wScale(wsc)
    , hScale(hsc)
    , smallFont(small)
    , fillColor(fc)
    , strokeColor(sc)
    {
        labels.push_back( SvgKeyboardButtonText(text, txtColor) );
    }

    SvgKeyboardButtonWithText( int xp, int yp, double wsc, double hsc, bool small, const std::string &fc, const std::string &sc
                             , const std::vector<SvgKeyboardButtonText> &texts
                             )
    : xPos(xp)
    , yPos(yp)
    , wScale(wsc)
    , hScale(hsc)
    , smallFont(small)
    , fillColor(fc)
    , strokeColor(sc)
    , labels(texts)
    {
    }

    std::vector<SvgKeyboardButtonText> normalizeLabels( ) const
    {
        return ::normalizeLabels(labels);
    }

};


inline
bool isLabelComma( const std::string &l )
{
    if (l.size()!=1) return false;

    char ch = l[0];

    if ( ch=='.'
      || ch==','
      || ch=='/'
      || ch=='?'
      || ch=='!'
      || ch=='\''
      || ch=='`'
      || ch==';'
      || ch==':'
      || ch=='('
      || ch==')'
      //|| ch==''
       )
       return true;

    return false;
}

inline
int getLabelExtraShift(const std::string &l)
{
    if (isLabelComma(l))
        return defKeyboardButtonCommaLabelShiftExtra;
    return 0;
}


//inline
//int printSvgKeyboardButtonHelperCalcLeft( )

std::ostream& operator<<( std::ostream& os, const SvgKeyboardButtonWithText &b )
{
    os<<SvgKeyboardButton( b.xPos, b.yPos, b.wScale, b.hScale, b.fillColor, b.strokeColor );

    int kh = (int)(defKeyboardButtonHeight*b.hScale*0.9);
    int kw = (int)(defKeyboardButtonHeight*b.wScale);

    //int kh2 = kh/2; 1/2 2/4 3/6 4/8 5/10
    int kh2 = 45*kh/100;
    int kw2 = kw/2;

    int textBaseX = b.xPos+defKeyboardButtonLabelOffsetX;
    int textBaseY = b.yPos+defKeyboardButtonLabelOffsetY+defKeyboardButtonLabelFontHeight;
    int lsh  =  defKeyboardButtonLeftLabelShift;
    int shft = defKeyboardButtonRightLabelShift;

    std::vector<SvgKeyboardButtonText> labels = b.normalizeLabels( );

    //bool useSmallFont = false;
    std::vector<SvgKeyboardButtonText>::const_iterator lit = labels.begin();
    /*
    for(; lit != labels.end(); ++lit)
    {
        if (lit->text.size()>=3)
           useSmallFont = true;
    }
    */
    std::string defFontStyle = b.smallFont ? "key_label_sm" : "key_label";
    std::string fontStyle = defFontStyle;


    if (labels.size()==1)
    {
        fontStyle = labels[0].text.size()<2 ? std::string("key_label") : defFontStyle;
        fontStyle = labels[0].text.size()>6 ? std::string("key_label_sm") : fontStyle;
        os<<SvgText( textBaseX+kw2/4-shft, textBaseY+kh2/2, labels[0].text, labels[0].color, fontStyle );
        return os;
    }


    if (labels.size()>0 && !labels[0].text.empty())
    {
        fontStyle = labels[0].text.size()<2 ? std::string("key_label") : defFontStyle;
        fontStyle = labels[0].text.size()>6 ? std::string("key_label_sm") : fontStyle;

        int wShift = lsh;
        if (labels.size()==2 && labels[0].text.size()>1 && labels[1].text.size()>1 )
        {
            wShift = -lsh;
        }
        os<<SvgText( textBaseX+wShift+getLabelExtraShift(labels[0].text)     , textBaseY    , labels[0].text, labels[0].color, fontStyle );
    }


    if (labels.size()>1 && !labels[1].text.empty())
    {
        fontStyle = labels[1].text.size()<2 ? std::string("key_label") : defFontStyle;
        fontStyle = labels[0].text.size()>6 ? std::string("key_label_sm") : fontStyle;

        int hShift = kh2;

        int wShift = lsh;
        if (labels.size()==2 && labels[0].text.size()>1 && labels[1].text.size()>1 )
        {
            hShift = kh/3;
            //wShift = 0; // lsh/3;
            wShift = -lsh;
        }
        os<<SvgText( textBaseX+wShift+getLabelExtraShift(labels[1].text)     , textBaseY+hShift, labels[1].text, labels[1].color, fontStyle );
    }

    if (labels.size()>2 && !labels[2].text.empty())
    {
        fontStyle = labels[2].text.size()<2 ? std::string("key_label") : defFontStyle;
        fontStyle = labels[0].text.size()>6 ? std::string("key_label_sm") : fontStyle;
        os<<SvgText( textBaseX+kw2-shft+getLabelExtraShift(labels[2].text), textBaseY    , labels[2].text, labels[2].color, fontStyle );
    }

    if (labels.size()>3 && !labels[3].text.empty())
    {
        fontStyle = labels[3].text.size()<2 ? std::string("key_label") : defFontStyle;
        fontStyle = labels[0].text.size()>6 ? std::string("key_label_sm") : fontStyle;
        os<<SvgText( textBaseX+kw2-shft+getLabelExtraShift(labels[3].text), textBaseY+kh2, labels[3].text, labels[3].color, fontStyle );
    }
    //os<<SvgText( b.xPos, b.yPos, b.lt, b.ltColor );

    return os;
}




typedef std::pair<std::string,std::string> TextPair;

inline 
TextPair makeTextPair( const std::string &a, const std::string &b )
{
    return std::make_pair( a, b );
}

inline 
TextPair makeTextPair( const std::string &t )
{
    // Special cases

    if (t.empty())
        return std::make_pair( std::string(), std::string() );
    else if (t=="/")
        return std::make_pair( t, std::string() );
    else if (t=="?//")
        return std::make_pair( std::string("?"), std::string("/") );
    else if (t=="//\\")
        return std::make_pair( std::string("/"), std::string("\\") );


    std::vector<std::string> pairVec = split( t, '/', false  /* skipEmpty */  );

    if (pairVec.empty())
        throw std::runtime_error("makeTextPair - empty result");
    if (pairVec.size()>2)
        throw std::runtime_error("makeTextPair - result too much");

    if (pairVec.size()==1)
    {
       return std::make_pair( t, std::string() ); // only first present
    }

    // Here we have two elements

    // Both elemens can't be empty

    if (pairVec[0].empty())
       return std::make_pair( std::string(), pairVec[1] );
    else if (pairVec[1].empty())
       return std::make_pair( pairVec[0], std::string() );
    else
       return std::make_pair( pairVec[0], pairVec[1] );

}


inline TextPair makeTop( const std::string &a )          { return makeTextPair( a, std::string() ); }
inline TextPair makeBottom( const std::string &a )       { return makeTextPair( std::string(), a ); }
inline TextPair makeBoth( const std::string &a, const std::string &b ) { return makeTextPair( a, b ); }

inline TextPair makeAlphaMain( const std::string &a )    { return makeTop( a ); }
inline TextPair makeAlphaAlter( const std::string &a )   { return makeBottom( a ); }
inline TextPair makeSingle( const std::string &a )       { return makeTop( a ); }
inline TextPair makeEmpty ( )                            { return makeBoth( std::string(), std::string() ); }


typedef std::vector<TextPair> TextPairsVector;


inline TextPair addTop       ( TextPairsVector &v, const std::string &a )  { v.push_back(makeTop(a)); }
inline TextPair addBottom    ( TextPairsVector &v, const std::string &a )  { v.push_back(makeBottom(a)); }
inline TextPair addBoth      ( TextPairsVector &v, const std::string &a, const std::string &b ) { v.push_back(makeBoth(a,b)); }

inline TextPair addAlphaMain ( TextPairsVector &v, const std::string &a )  { v.push_back(makeAlphaMain(a)); }
inline TextPair addAlphaAlter( TextPairsVector &v, const std::string &a )  { v.push_back(makeAlphaAlter(a)); }
inline TextPair addSingle    ( TextPairsVector &v, const std::string &a )  { v.push_back(makeSingle(a)); }
inline TextPair addEmpty     ( TextPairsVector &v )                        { v.push_back(makeEmpty()); }

inline void addPair ( TextPairsVector &v, const std::string &t )  { v.push_back(makeTextPair(t)); }
inline void addPair ( TextPairsVector &v )                        { v.push_back(makeEmpty()); }


inline bool isTextPairEmpty    ( const TextPair &tp )   { return tp.first.empty()  && tp.second.empty(); }
inline bool isTextPairFirstOnly( const TextPair &tp )   { return !tp.first.empty() && tp.second.empty(); }
inline bool isTextString       ( const std::string &t ) { return t.size()>1; }
inline bool isTextSymbol       ( const std::string &t ) { return !isTextString(t); }
inline bool isTextPairSymbol   ( const TextPair &tp )   { return isTextSymbol(tp.first) && isTextSymbol(tp.second); } // оба либо пусты, либо одиночные символы
inline bool isTextPairText     ( const TextPair &tp )   { return isTextString(tp.first) && isTextString(tp.second); }
inline bool isTextPairAlpha    ( const TextPair &tp )   { if (!tp.second.empty() || tp.first.size()!=1) return false; char ch = tp.first[0]; return (ch>='A' && ch<='Z') || (ch>='a' && ch<='z'); }
inline bool isTextPairFirstDigit(const TextPair &tp )   { if (tp.first.size()!=1) return false; char ch = tp.first[0]; return (ch>='0' && ch<='9'); }
inline bool isTextPairFirstAriphm(const TextPair &tp )  { if ((tp.first=="/" || tp.first=="*" || tp.first=="-" || tp.first=="+") && tp.second.empty()) return true; return false; }
inline bool isTextPairFirstNumPadDot(const TextPair &tp){ if ((tp.first==".") && !tp.second.empty()) return true; return false; }
inline bool isTextPairSecondUtf(const TextPair &tp)     { if (tp.second.empty()) return false; char ch = tp.second[0]; return ((unsigned char)ch)>=128; }



inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonTexts( const std::string &color, const TextPair &tp )
{
    return makeSvgKeyboardButtonTexts( color, tp.first, tp.second );
}

enum KeyLabelType
{
    keyLabelCommon,
    keyLabelHasAlter
};

inline
std::vector<SvgKeyboardButtonText> makeSvgKeyboardButtonText( const TextPair &tpMain
                                                            , const TextPair &tpAlter
                                                            , const std::string &colorMain
                                                            , const std::string &colorAlter
                                                            , bool makeReadyForSingle
                                                            , KeyLabelType &klt
                                                            )
{
    // Esc/Tab/NumPad keys etc
    /*
    if ( isTextPairFirstOnly(tpMain) 
      // && isTextString(tpMain.first) 
      && isTextPairEmpty(tpAlter)
       )
    {
        return makeSvgKeyboardButtonTexts( colorMain, tpMain );
        //return makeSvgKeyboardButtonTexts( makeSvgKeyboardButtonTexts( colorMain, tpMain )
        //                                 , makeSvgKeyboardButtonTexts( colorAlter, 2 )
        //                                 );
    }
    */

    // PrtSc/SysRq  Scroll/Lock  Pause/Break  NumPad keys
    //if ( /* isTextPairText(tpMain) && */  isTextPairEmpty(tpAlter))
    if ( isTextString(tpMain.first) && isTextPairEmpty(tpAlter))
    {
        klt = keyLabelCommon;
        return makeSvgKeyboardButtonTexts( colorMain, tpMain );
        //return makeSvgKeyboardButtonTexts( makeSvgKeyboardButtonTexts( colorMain, tpMain )
        //                                 , makeSvgKeyboardButtonTexts( colorAlter, 2 )
        //                                 );
    }

    // NumPad digit
    if (isTextPairFirstDigit(tpMain) || isTextPairFirstAriphm(tpMain) || isTextPairFirstNumPadDot(tpMain))
    {
        klt = keyLabelCommon;
        return makeSvgKeyboardButtonTexts( colorMain, tpMain );
    }


    klt = keyLabelHasAlter;

    if (isTextPairAlpha(tpMain) || isTextPairSecondUtf(tpAlter))
    {
        return makeSvgKeyboardButtonTexts( makeSvgKeyboardButtonTexts( colorMain, tpMain )
                                         , makeSvgKeyboardButtonTexts( colorAlter, tpAlter )
                                         );
    }

    if (!makeReadyForSingle)
    {
        return makeSvgKeyboardButtonTexts( makeSvgKeyboardButtonTexts( colorMain, tpMain )
                                         , makeSvgKeyboardButtonTexts( colorAlter, tpAlter )
                                         );
    }
    
    TextPair tpAlterCopy = tpAlter;
    if (tpAlterCopy.first.empty())
        tpAlterCopy.first = tpMain.first;
    if (tpAlterCopy.second.empty())
        tpAlterCopy.second = tpMain.second;

    return makeSvgKeyboardButtonTexts( makeSvgKeyboardButtonTexts( colorMain, tpMain )
                                     , makeSvgKeyboardButtonTexts( colorAlter, tpAlterCopy )
                                     );
}

enum KeyboardLayoutType
{
    kltBoth,
    kltMain,
    kltAlter

};


inline
std::vector< std::vector<SvgKeyboardButtonText> > makeSvgKeyboardButtonTexts( const TextPairsVector *pMain
                                                             , const TextPairsVector *pAlter
                                                             , const std::string &colorMain
                                                             , const std::string &colorAlter
                                                             , KeyboardLayoutType klt
                                                             )
{
    TextPairsVector tmpVec;
    TextPair        tmpPair;

    std::vector< std::vector<SvgKeyboardButtonText> > res;

    if (pAlter==0)
        pAlter = &tmpVec;

    TextPairsVector::const_iterator mit = pMain->begin();
    TextPairsVector::const_iterator ait = pAlter->begin();

    TextPairsVector::const_iterator mEnd = pMain->end();
    TextPairsVector::const_iterator aEnd = pAlter->end();

    for(; mit!=mEnd; ++mit)
    {
        const TextPair &mp = *mit;
        const TextPair &ap = ait!=aEnd ? *ait : tmpPair;
        KeyLabelType keyLabelType = keyLabelCommon;

        std::vector<SvgKeyboardButtonText> keyLabels = makeSvgKeyboardButtonText( mp, ap, colorMain, colorAlter, klt!=kltBoth /* makeReadyForSingle */, keyLabelType );

        if (keyLabelType==keyLabelCommon || klt==kltMain)
        {
            if (keyLabels.size()>2)
               keyLabels.erase( keyLabels.begin()+2, keyLabels.end() );
        }

        if (keyLabelType!=keyLabelCommon && klt==kltAlter)
        {
            // clear main labels
            if (keyLabels.size()>0)
               keyLabels[0].text.clear();
            if (keyLabels.size()>1)
               keyLabels[1].text.clear();
        }

        if (ait!=aEnd)
            ++ait;

        res.push_back(keyLabels);
    }

    return res;

}

/*
    Надо описать строку
    Высота? Что ещё?

    Вектор размеров кнопок
    Ссылка на основную (английскую) раскладку
    Ссылка на альтернативную (русскую) раскладку
     

*/

enum GapType
{
    gapEnd  ,   // last item
    gapKey  ,   // key
    gapSmk  ,   // key with small text
    gapDbl  ,   // double heigh key
    gapDbs  ,   // double heigh key with small text
    gapSkip ,
    gapFn   ,
    gapIns  ,
    gapNum
};


enum SvgKeyboardRowType
{
    skrtEnd,
    skrtNormal,
    skrtNormalFn,
    skrtVertical
};



// 1 - forefinger.
// 2 - middle finger.
// 3 - ring finger.
// 4 - little finger.
enum Finger
{
    fgD, // default finger color
    // left hand
    fgT , // thumb finger (big palec)

    fglM, // forefinger. color with marker (ukaz palec)
    fgl1, // forefinger (ukaz palec)
    fgl2, // mid palec
    fgl3, // unnamed palec
    fgl4, // mizinec
    // right hand
    fgrM, // forefinger. color with marker
    fgr1,
    fgr2,
    fgr3,
    fgr4,

    fgNM,

};


inline
unsigned fingerToIndex(Finger f)
{
    switch(f)
    {
        case fgD :  return 0;
        case fgT :  return 1; // thumb finger (big palec)

        case fglM:  return 2;
        case fgl1:  return 2;
        case fgl2:  return 3;
        case fgl3:  return 4;
        case fgl4:  return 5;

        case fgrM:  return 6;
        case fgr1:  return 6;
        case fgr2:  return 7;
        case fgr3:  return 8;
        case fgr4:  return 9;
        case fgNM:  return 7;
    }
}



struct SvgKeyInfo
{
    GapType  gapType; // some kind of gap or key
    double   scale;   // horizontal
    Finger   finger;
};

struct SvgKeysRowInfo
{
    SvgKeyboardRowType  rowType;
    double              scale;  // vertical

    SvgKeyInfo          *pKeys;
    TextPairsVector     *pMain;
    TextPairsVector     *pAlter;

};


// const TextPairsVector *pMain

/*
struct SvgKeyboardButtonText
{
    std::string text;
    std::string color;
};

std::vector<SvgKeyboardButtonText> normalizeLabels( const std::vector<SvgKeyboardButtonText> &labels )

*/





//@newcommand[rect][\
//<rect x="#1" y="#2" width="#3" height="#4" rx="#5" ry="#6" fill="#7" stroke="#8" stroke-width="#9" />\
//]

