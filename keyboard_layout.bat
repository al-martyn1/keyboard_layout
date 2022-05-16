set DEFS=

call cxx /EHsc kbd_layout_gen.cpp >kbd_layout_gen.log
@rem if exist kbd_en.svg del kbd_en.svg
kbd_layout_gen svg\kbd_layout_en.svg en
kbd_layout_gen svg\kbd_layout_ru.svg ru
kbd_layout_gen svg\kbd_layout_all.svg all

kbd_layout_gen svg\kbd_layout_en_pale.svg en pale
kbd_layout_gen svg\kbd_layout_ru_pale.svg ru pale
kbd_layout_gen svg\kbd_layout_all_pale.svg all pale

