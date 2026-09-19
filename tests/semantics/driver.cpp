#include <crails/utils/semantics.hpp>

#undef NDEBUG
#include <cassert>

int main()
{
  using namespace std;

  assert(Crails::underscore("Coucou petite  Perruche") == "coucou_petite_perruche");
  assert(Crails::underscore("coucou-petite-perruche") == "coucou_petite_perruche");
  assert(Crails::camelize("coucou petite perruche") == "CoucouPetitePerruche");
  assert(Crails::camelize("coucou petite perruche", Crails::LowerCamelcase) == "coucouPetitePerruche");
  assert(Crails::camelize("  un_deux_trois") == "UnDeuxTrois");
  assert(Crails::dasherize("   lettre a mots ") == "lettre-a-mots");
  assert(Crails::dasherize("LettreAMots") == "lettre-a-mots");
  assert(Crails::dasherize("_lettreA_mots") == "lettre-a-mots");
  assert(Crails::pluralize("one") == "ones");
  assert(Crails::pluralize("worry") == "worries");
  assert(Crails::singularize("ones") == "one");
  assert(Crails::singularize("worries") == "worry");
  assert(Crails::strip("   to  strip    ") == "to  strip");
  assert(Crails::strip("++strippable+", '+') == "strippable");
  assert(Crails::uppercase("Impots et prelevements sociaux 2024") == "IMPOTS ET PRELEVEMENTS SOCIAUX 2024");
  assert(Crails::lowercase("HAPPY Thursday!0~") == "happy thursday!0~");

  return 0;
}
