#include <string>
#include <list>
#include "wordlists.cpp"

namespace px
{
    namespace wordlists
    {
        void populateWordLists()
        {
            //? racist
                px::wordlists::bad::racist.add("NIGGA");
                px::wordlists::bad::racist.add("schlitzauge");
                px::wordlists::bad::racist.add("nazi");
            //? swearing
                px::wordlists::bad::swearing.add("hurensohn");
                px::wordlists::bad::swearing.add("bastard");
                px::wordlists::bad::swearing.add("son of a bitch");
                px::wordlists::bad::swearing.add("Hijo de puta");
                px::wordlists::bad::swearing.add("motherfucker");
                px::wordlists::bad::swearing.add("schlampe");
                px::wordlists::bad::swearing.add("slut");
                px::wordlists::bad::swearing.add("cocksucker");
                px::wordlists::bad::swearing.add("Fuck");
                px::wordlists::bad::swearing.add("BullShit");
                px::wordlists::bad::swearing.add("Shit");
                px::wordlists::bad::swearing.add("Piss of");
                px::wordlists::bad::swearing.add("Asshole");
                px::wordlists::bad::swearing.add("Bitch");
                px::wordlists::bad::swearing.add("Cunt");
                px::wordlists::bad::swearing.add("Snatch");
                px::wordlists::bad::swearing.add("Snitch");
                px::wordlists::bad::swearing.add("DickHead");
            //! i just don't want to see this shit on the internet... like 4real... (im fucking disappointed in humanity)
                px::wordlists::bad::all.add("bigdickenergy");
                px::wordlists::bad::all.add("smalldickenergy");

            for(std::string I : px::wordlists::bad::racist.words){px::wordlists::bad::all.add(I);}
            for(std::string I : px::wordlists::bad::swearing.words){px::wordlists::bad::all.add(I);}
            for(std::string I : px::wordlists::bad::homophobe.words){px::wordlists::bad::all.add(I);}
        }
    }
}