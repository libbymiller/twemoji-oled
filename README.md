# twemoji-oled

Tiny emojis for an oled screen based on twitter's twemoji

The wemos code is messy.

The screens are these:

https://wiki.wemos.cc/products:d1_mini_shields:oled_shield

To parse emojis to get their name, use https://github.com/twitter/twemoji/blob/gh-pages/2/twemoji.js

        var twe = twemoji.parse(emoji[i]);
        //<img class="emoji" draggable="false" alt="🔞" src="https://twemoji.maxcdn.com/2/72x72/1f51e.png"/>
        twe = twe.replace(/.*72x72/,"48x48");
        twe = twe.replace(".png\"/>","");
        twe = twe.replace(/[^a-zA-Z0-9\/]/,""); //for weird emojis
