#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "kbd_commons.h"
#include "kbd.h"


int main(int argc, char* argv[])
{
    if (argc<3)
    {
        std::cerr<<"Usage: kbd_layout_gen file layout\n";
        return 1;
    }

    KeyboardLayoutType keyboardLayoutType = kltBoth;
    if (std::string(argv[2])=="en")
       keyboardLayoutType = kltMain;
    else if (std::string(argv[2])=="ru")
       keyboardLayoutType = kltAlter;
    else if (std::string(argv[2])=="all")
       keyboardLayoutType = kltBoth;
    else
    {
        std::cerr<<"Invalid layout name.\nUsage: kbd_layout_gen file layout\n";
        return 1;
    }

    bool paleMode = false;
    if (argc>3 && std::string(argv[3])=="pale")
        paleMode = true;



    std::ofstream os( argv[1] ); // "kbd_en.svg"


    os<<svgBegin;

    //os<<SvgRect( 10, 10, 30, 40, 3, 3, "yellow", "black", 2 )<<"\n";

    //os<<SvgGenericKeyboardButton( 50, 10, 40, 40, "green", "black" )<<"\n";

    //os<<SvgKeyboardButton( 100, 10, 1.0, "blue", "black" )<<"\n";
    //os<<SvgKeyboardButton( 150, 10, 1.5, "red" , "black" )<<"\n";

    //os<<"<text x=\"120\" y=\"135\" class=\"key_label\">Test</text>\n";

    //os<<SvgText( 120, 160, "Aaaa", "magenta" )<<"\n";

    //os<<SvgKeyboardButtonWithText( 40, 40, 1.0, 1.0, "yellow", "green", SvgKeyboardButtonTexts("Q", "@", "#", "Й"), "black" )<<"\n";

    //os<<SvgKeyboardButtonWithText( 40, 40, 1.0, 1.0, "yellow", "green", makeSvgKeyboardButtonTexts("black", "?", "/", ",", ".") )<<"\n";
    //os<<SvgKeyboardButtonWithText( 90, 40, 1.0, 1.0, "yellow", "green", makeSvgKeyboardButtonTexts("black", "W") )<<"\n";
    //os<<SvgKeyboardButtonWithText( 40, 90, 1.0, 1.0, "yellow", "green", makeSvgKeyboardButtonTexts("black", "Q", "", "", "Й") )<<"\n";

    /*
    #define aTp   addTop
    #define aBt   addBottom
    #define aBh   addBoth
                               
    #define aAm   addAlphaMain
    #define aAa   addAlphaAlter
    #define aSi   addSingle
    #define aEy   addEmpty
    */

    #define adp  addPair

    
    // Key labels config

    TextPairsVector fl; // Function keys line

    adp(fl, "Esc"); 
    adp(fl,"F1");adp(fl,"F2");adp(fl,"F3");adp(fl,"F4");adp(fl,"F5");adp(fl,"F6");adp(fl,"F7");adp(fl,"F8");adp(fl,"F9");adp(fl,"F10");adp(fl,"F11");adp(fl,"F12");
    adp(fl,"PrtSc/SysRq");adp(fl,"Scroll/Lock");adp(fl,"Pause/Break");


    TextPairsVector dl; // Digit keys line
    adp(dl,"~/`"); 
    adp(dl,"!/1");adp(dl,"@/2");adp(dl,"#/3");adp(dl,"$/4");adp(dl,"%/5");adp(dl,"^/6");adp(dl,"&/7");adp(dl,"*/8");adp(dl,"(/9");adp(dl,")/0");
    adp(dl,"_/-");adp(dl,"+/=");adp(dl,"Backspace");
    adp(dl,"Ins");adp(dl,"Home");adp(dl,"PgUp");adp(dl,"Num/Lock");adp(dl,"/");adp(dl,"*");adp(dl,"-");


    TextPairsVector ql; // qwerty line (main)
    adp(ql,"Tab");
    adp(ql,"Q");adp(ql,"W");adp(ql,"E");adp(ql,"R");adp(ql,"T");adp(ql,"Y");adp(ql,"U");adp(ql,"I");adp(ql,"O");adp(ql,"P");adp(ql,"{/[");adp(ql,"}/]");adp(ql, "|/\\");
    adp(ql,"Del");adp(ql,"End");adp(ql,"PgDn");
    adp(ql,"7/Home");adp(ql,"8/Up");adp(ql,"9/PgUp");adp(ql,"+");
    

    TextPairsVector al; // asdf line (main)
    adp(al,"Caps Lock");
    adp(al,"A");adp(al,"S"); adp(al,"D");adp(al,"F");adp(al,"G");adp(al,"H");adp(al,"J");adp(al,"K"); adp(al,"L");adp(al,":/;");adp(al,"\"/\'");
    adp(al,"Enter");
    //adp(al); adp(al); adp(al); // skip 
    adp(al,"4/Left");adp(al,"5/ ");adp(al,"6/Right");


    TextPairsVector zl; // zxcv line (main)
    adp(zl,"Shift");
    adp(zl,"Z");adp(zl,"X");adp(zl,"C");adp(zl,"V");adp(zl,"B");adp(zl,"N");adp(zl,"M");adp(zl,"</,");adp(zl,">/.");adp(zl,"?//");
    adp(zl,"Shift");
    adp(zl,"Up");
    adp(zl,"1/End");adp(zl,"2/Down");adp(zl,"3/PgDn");adp(zl,"Enter");


    TextPairsVector sl; // space line
    adp(sl,"Ctrl");adp(sl,"Win");adp(sl,"Alt");adp(sl,""); /* Space */ adp(sl,"Alt Gr");adp(sl,"Win");adp(sl,"Menu");adp(sl,"Ctrl");
    adp(sl,"Left");adp(sl,"Down");adp(sl,"Right");
    adp(sl,"0/Ins");adp(sl,"./Del");

    //TextPairsVector vl; // vertical line
    //adp(vl,"+");adp(vl,"Enter");

    
    TextPairsVector da; // Digit keys line alter (russian)
    adp(da,"/Ё");
    adp(da);adp(da,"\"");adp(da,"№");adp(da,";");adp(da);adp(da,":");adp(da,"?");//adp(da);adp(da);adp(da);
    //adp(da);adp(da);adp(da);
    //adp(da);adp(da);adp(da);adp(da);adp(da);adp(da);adp(da);


    TextPairsVector qa; // qwerty line alter (russian)
    adp(qa);
    adp(qa,"/Й");adp(qa,"/Ц");adp(qa,"/У");adp(qa,"/К");adp(qa,"/Е");adp(qa,"/Н");adp(qa,"/Г");adp(qa,"/Ш");adp(qa,"/Щ");adp(qa,"/З");adp(qa,"/Х");adp(qa,"/Ъ");adp(qa, "//\\");
    //adp(qa);adp(qa);adp(qa);
    //adp(ql);adp(ql);adp(ql);


    TextPairsVector aa; // asdf line alter (russian)
    adp(aa);
    adp(aa,"/Ф");adp(aa,"/Ы"); adp(aa,"/В");adp(aa,"/А");adp(aa,"/П");adp(aa,"/Р");adp(aa,"/О");adp(aa,"/Л"); adp(aa,"/Д");adp(aa,"/Ж");adp(aa,"/Э");
    //adp(aa);
    //adp(aa);adp(aa);adp(aa);


    TextPairsVector za; // zxcv line alter (russian)
    adp(za);
    adp(za,"/Я");adp(za,"/Ч");adp(za,"/С");adp(za,"/М");adp(za,"/И");adp(za,"/Т");adp(za,"/Ь");adp(za,"/Б");adp(za,"/Ю");adp(za,",/.");
    //adp(za);
    //adp(za);
    //adp(za);adp(za);adp(za);


    // Keys geometry

    // Function keys
    SvgKeyInfo fg[] = { {gapKey,1.0,fgl4 }, {gapSkip,1.0,fgD}
                      ,                     {gapKey,1.0,fgl4},  {gapKey,1.0,fgl3}, {gapKey,1.0,fgl2}, {gapKey,1.0,fgl1} // F1-F4
                      , {gapFn ,1.0,fgD  }, {gapKey,1.0,fgr1},  {gapKey,1.0,fgr2}, {gapKey,1.0,fgr3}, {gapKey,1.0,fgr4} // F5-F8
                      , {gapFn ,1.0,fgD  }, {gapKey,1.0,fgr1},  {gapKey,1.0,fgr2}, {gapKey,1.0,fgr3}, {gapKey,1.0,fgr4} // F9-F12
                      , {gapIns,1.0,fgD  }, {gapSmk,1.0,fgr1},  {gapSmk,1.0,fgr2}, {gapSmk,1.0,fgr3}
                      //,                {gapNum ,1.0},   {gapKey,1.0}, {gapKey,1.0}, {gapKey,1.0}, {gapKey,1.0}
                      , {gapEnd,1.0,fgD}
                      };

    // Digits row
    SvgKeyInfo dg[] = { {gapKey,1.0 ,fgl4}, {gapKey,1.0,fgl4 }, {gapKey,1.0,fgl4}, {gapKey,1.0,fgl3}, {gapKey,1.0,fgl2}, {gapKey,1.0,fgl1}, {gapKey,1.0,fgl1 } // ~ 1 2 3 4 5 6
                      ,                     {gapKey,1.0,fgr1 }, {gapKey,1.0,fgr1}, {gapKey,1.0,fgr2}, {gapKey,1.0,fgr3}, {gapKey,1.0,fgr4}, {gapKey,1.0,fgr4 } // 7 8 0 - =
                      ,                     {gapKey,2.16,fgr4}                                                                             // BS
                      , {gapIns,1.0 ,fgD }, {gapSmk,1.0,fgr1 }, {gapSmk,1.0,fgr2}, {gapSmk,1.0,fgr3}
                      , {gapNum,1.0 ,fgD }, {gapSmk,1.0,fgr1 }, {gapKey,1.0,fgr2}, {gapKey,1.0,fgr3}, {gapKey,1.0,fgr4}
                      , {gapEnd, 1.0,fgD }
                      };

    // qwerty
                             // 1.58
    SvgKeyInfo qg[] = { {gapKey,1.60,fgl4}, {gapKey,1.0,fgl4 }, {gapKey,1.0,fgl3}, {gapKey,1.0,fgl2}, {gapKey,1.0,fgl1}, {gapKey,1.0,fgl1}
                      ,                     {gapKey,1.0,fgr1 }, {gapKey,1.0,fgr1}, {gapKey,1.0,fgr2}, {gapKey,1.0,fgr3}, {gapKey,1.0,fgr4}, {gapKey,1.0,fgr4}, {gapKey,1.0,fgr4}
                      ,                     {gapKey,1.58,fgr4}
                      , {gapIns,1.0 ,fgl4}, {gapSmk,1.0,fgr1 }, {gapSmk,1.0,fgr2}, {gapSmk,1.0,fgr3}
                      , {gapNum,1.0 ,fgD }, {gapSmk,1.0,fgr1 }, {gapSmk,1.0,fgr2}, {gapSmk,1.0,fgr3}, {gapDbl,1.0,fgr4} 
                      , {gapEnd,1.0 ,fgD }
                      };

    // asdf
    SvgKeyInfo ag[] = { {gapKey,1.88,fgl4}, {gapKey,1.0,fgl4 }, {gapKey,1.0,fgl3}, {gapKey,1.0,fgl2}, {gapKey,1.0,fglM}, {gapKey,1.0,fgl1}
                      ,                     {gapKey,1.0,fgr1 }, {gapKey,1.0,fgrM}, {gapKey,1.0,fgr2}, {gapKey,1.0,fgr3}, {gapKey,1.0,fgr4 }, {gapKey,1.0,fgr4}
                      ,                     {gapKey,2.45,fgr4}  // 2.43
                      , {gapIns,1.0,fgD  }, {gapSkip,1.0,fgD }, {gapSkip,1.0,fgD}, {gapSkip,1.0,fgD}
                      , {gapNum,1.0,fgD  }, {gapSmk,1.0,fgr1 }, {gapSmk,1.0,fgNM}, {gapSmk,1.0,fgr3}
                      , {gapEnd, 1.0,fgD }
                      };
    // zxcv
                             // 2.45
    SvgKeyInfo zg[] = { {gapKey,2.45,fgl4}, {gapKey,1.0,fgl4 }, {gapKey,1.0,fgl3}, {gapKey,1.0,fgl2}, {gapKey,1.0,fgl1}, {gapKey,1.0,fgl1}
                      ,                     {gapKey,1.0,fgr1 }, {gapKey,1.0,fgr1}, {gapKey,1.0,fgr2}, {gapKey,1.0,fgr3}, {gapKey,1.0,fgr4}
                      ,                     {gapKey,3.05,fgr4}  // 3.0
                      , {gapIns,1.0,fgD  }, {gapSkip,1.0,fgD }, {gapSmk,1.0,fgr2}, {gapSkip,1.0,fgD}
                      , {gapNum,1.0,fgD  }, {gapSmk,1.0,fgr1 }, {gapSmk,1.0,fgr2}, {gapSmk ,1.0,fgr3}, {gapDbs,1.0,fgr4} 
                      , {gapEnd, 1.0,fgD }
                      };

    // space
    SvgKeyInfo sg[] = { {gapKey,1.6 ,fgr4}, {gapKey,1.0,fgr3 }, {gapKey,1.625,fgT} // 1.68
                      , {gapKey,6.85,fgT } // 6.75
                      , {gapKey,1.3 ,fgT }, {gapKey,1.3 ,fgr1}, {gapKey,1.3,fgr2}, {gapKey,1.3,fgr3} // ... 1.26 1.28
                      , {gapIns,1.0 ,fgD }, {gapSmk,1.0 ,fgr1}, {gapSmk,1.0 ,fgr2},{gapSmk,1.0,fgr3}
                      , {gapNum,1.0 ,fgD }, {gapSmk,2.15,fgr1}, {gapSmk,1.0,fgr3}
                      , {gapEnd, 1.0,fgD }
                      };


    // https://www.december.com/html/spec/colorsvg.html
    std::vector<std::string> fingerColors;

    push_back_helper(fingerColors,std::string("white"));

    std::vector<std::string> fingerMarkerColors;
    std::string mainColor;
    std::string altColor;
    std::string buttonBorderColor;


    if (paleMode)
    {
        push_back_helper(fingerColors,std::string("lightskyblue")); // deepskyblue
      
        push_back_helper(fingerColors,std::string("lavender")); // blue lightskyblue aqua deepskyblue cyan aquamarine
        push_back_helper(fingerColors,std::string("lemonchiffon")); // yellow
        push_back_helper(fingerColors,std::string("blanchedalmond")); // orange
        push_back_helper(fingerColors,std::string("mistyrose")); // red lightpink
      
        push_back_helper(fingerColors,std::string("lightcyan")); // cian
        push_back_helper(fingerColors,std::string("lemonchiffon")); // yellow
        push_back_helper(fingerColors,std::string("blanchedalmond")); // orange
        push_back_helper(fingerColors,std::string("mistyrose")); // red mistyrose


        push_back_helper(fingerMarkerColors,std::string("red"));
        push_back_helper(fingerMarkerColors,std::string("red"));

        mainColor = "black";
        altColor  = "maroon"; // "orange";
        buttonBorderColor = "black";

    }
    else
    {
        push_back_helper(fingerColors,std::string("deepskyblue")); // lightskyblue deepskyblue cyan
      
        push_back_helper(fingerColors,std::string("lightskyblue")); // blue lightskyblue aqua deepskyblue cyan aquamarine lavender
        push_back_helper(fingerColors,std::string("khaki")); // yellow
        push_back_helper(fingerColors,std::string("lightsalmon")); // orange blanchedalmond
        push_back_helper(fingerColors,std::string("lightpink")); // red lightpink
      
        push_back_helper(fingerColors,std::string("palegreen")); // cian lightseagreen
        push_back_helper(fingerColors,std::string("khaki")); // yellow lemonchiffon
        push_back_helper(fingerColors,std::string("lightsalmon")); // orange
        push_back_helper(fingerColors,std::string("lightpink")); // red mistyrose


        push_back_helper(fingerMarkerColors,std::string("red"));
        push_back_helper(fingerMarkerColors,std::string("red"));

        mainColor = "black"; // mediumblue
        altColor  = "red"; // "orange"; // tomato
        buttonBorderColor = "gray";

    }



    SvgKeysRowInfo rows[] = { { skrtNormalFn, 0.75, &fg[0], &fl,   0 }
                            , { skrtNormal  , 1.0 , &dg[0], &dl, &da }
                            , { skrtNormal  , 1.0 , &qg[0], &ql, &qa }
                            , { skrtNormal  , 1.0 , &ag[0], &al, &aa }
                            , { skrtNormal  , 1.0 , &zg[0], &zl, &za }
                            , { skrtNormal  , 1.0 , &sg[0], &sl,   0 }

                            , { skrtEnd     , 1.0 , 0     , 0  ,   0 }
                            };

    int frameOffsetX = 10;
    int frameOffsetY = 10;
    int frameRound   = 3;

    int startX = 50;
    int startY = 50;
    int x = startX;
    int y = startY;
    int xMax = x;
    int yMax = y;


    int vGap = defNormalHeightGap;

    const SvgKeysRowInfo *pRow = &rows[0];

    try
    {
        for(; pRow->rowType!=skrtEnd; ++pRow )
        {
            if (pRow->rowType==skrtNormalFn)
               vGap = defFnHeightGap;
            else
               vGap = defNormalHeightGap;
       
            const SvgKeyInfo          *pKeys  = pRow->pKeys ;
            const TextPairsVector     *pMain  = pRow->pMain ;
            const TextPairsVector     *pAlter = pRow->pAlter;
       
            std::vector< std::vector<SvgKeyboardButtonText> > labels 
                = makeSvgKeyboardButtonTexts( pMain, pAlter, mainColor, altColor, keyboardLayoutType );
       
            std::vector< std::vector<SvgKeyboardButtonText> >::const_iterator lit = labels.begin();
       
            for( ; pKeys->gapType!=gapEnd; ++pKeys )
            {
                switch(pKeys->gapType)
                {
                    case gapDbl :
                    case gapDbs :
                    case gapSmk :
                    case gapKey :
                                {
                                    unsigned fingerIndex = fingerToIndex(pKeys->finger);
                                    bool hasFingerMarker = pKeys->finger==fglM || pKeys->finger==fgrM || pKeys->finger==fgNM;

                                    std::vector<SvgKeyboardButtonText> keyLabels;
                                    if (lit!=labels.end())
                                    {
                                        keyLabels = *lit;
                                        ++lit;
                                    }

                                    double hScale = pRow->scale;
                                    if (pKeys->gapType==gapDbl || pKeys->gapType==gapDbs)
                                    {
                                        double btnHeigh = 2*defKeyboardButtonHeight*hScale + defKeyboardButtonHeight*defNormalHeightGapScale;
                                        hScale = btnHeigh / defKeyboardButtonHeight;
                                    }

                                    bool bSmallFont = pKeys->gapType==gapSmk || pKeys->gapType==gapDbs;
                                    os<<SvgKeyboardButtonWithText( x, y, pKeys->scale, hScale, bSmallFont, fingerColors[fingerIndex] /* "white" */ , buttonBorderColor, keyLabels )<<"\n";

                                    if (hasFingerMarker)
                                    {
                                        int markerX      = x + (int)((defKeyboardButtonWidth*pKeys->scale)/2.0);
                                        int markerLeft   = markerX - (int)(defKeyboardButtonWidth*0.2);
                                        int markerRight  = markerX + (int)(defKeyboardButtonWidth*0.2);
                                        int markerBase   = y + (int)(defKeyboardButtonHeight*pRow->scale);
                                        int markerBottom = markerBase   - (int)(defKeyboardButtonHeight*0.09 );
                                        int markerTop    = markerBottom - (int)(defKeyboardButtonHeight*0.04);

                                        std::string markerColor = fingerMarkerColors[ pKeys->finger==fglM ? 0 : 1 ];
                                        // darkorange                                                                                     // greenyellow lime lawngreen gold
                                        os<<SvgRect( markerLeft, markerTop, markerRight-markerLeft, markerBottom-markerTop, 0, 0, "white", markerColor, 1 );
                                    }

                                    x += (int)(defKeyboardButtonWidth*pKeys->scale) + defNormalWidthGap;
                                }
                                
                         break;
       
                    case gapSkip: x += (int)(defKeyboardButtonWidth*pKeys->scale) + defNormalWidthGap;
                         break;
       
                    case gapFn  : x += defFnGap;
                         break;
       
                    case gapIns : x += defInsGap;
                         break;
       
                    case gapNum : x += defNumGap;
                         break;
       
                } // switch(pKeys->gapType)

                if (xMax<x)
                    xMax = x;

            } // for( ; pKeys->gapType!=gapEnd; ++pKeys )

            y += (int)(defKeyboardButtonHeight*pRow->scale) + vGap;
            x = startX;

            if (yMax<y)
                yMax = y;

        } // for(; pRow->rowType!=skrtEnd...


        os<<SvgTransparentRect( startX-frameOffsetX, startY-frameOffsetY, xMax-startX+2*frameOffsetX, yMax-startY+2*frameOffsetY, frameRound, frameRound, "black", 3 );

    }
    catch(const std::exception &e)
    {
        std::cerr<<"Error: "<<e.what()<<"\n";
    }
    catch(...)
    {
        std::cerr<<"Error: unknown error\n";
    }

    //keyboardLayoutType
    os<<svgEnd;
    //os<<"eeee";

    return 0;
}


