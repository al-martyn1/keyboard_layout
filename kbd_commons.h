#pragma once

int xPos = 0;
int yPos = 0;

int defKeyboardButtonRoundingX              = 3 ;
int defKeyboardButtonRoundingY              = 3 ;
int defKeyboardButtonStrokeThickness        = 2 ;
int defKeyboardButtonHeight                 = 36;
int defKeyboardButtonWidth                  = defKeyboardButtonHeight;

int defKeyboardButtonLabelOffsetX           = 5 ;
int defKeyboardButtonLabelOffsetY           = 4 ;
int defKeyboardButtonLabelFontHeight        = 12;

int defKeyboardButtonLeftLabelShift         = 1 ;
int defKeyboardButtonRightLabelShift        = 3 ;
int defKeyboardButtonCommaLabelShiftExtra   = 2 ; // , . / ? ! ` ; : ' ( ) ...

double defNormalWidthGapScale  = 0.17;
double defNormalHeightGapScale = 0.17;

int defNormalWidthGap     = (int)(defKeyboardButtonHeight*defNormalWidthGapScale);
int defNormalHeightGap    = (int)(defKeyboardButtonHeight*defNormalHeightGapScale);
int defFnHeightGap        = (int)(defKeyboardButtonHeight*0.4);
int defFnGap              = (int)(defKeyboardButtonHeight*0.575);
int defInsGap             = (int)(defKeyboardButtonHeight*0.6);
int defNumGap             = (int)(defKeyboardButtonHeight*0.6);


// Font size - see svgBegin var, style section