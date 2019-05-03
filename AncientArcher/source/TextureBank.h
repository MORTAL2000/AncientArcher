#pragma once
#include<string>

/* requirements on TextureBank image use:
   1.  must be a .png
   2.  must have alpha channel
   3.  must have width divisable by 4
*/
class TextureBank {
public:
  TextureBank();

  /* loadTexture adds a new texture to the bank of usable textures */
  void loadTexture(std::string path);

  /* signal graphics card to use a certain texture for the upcoming draw functions */
  void activate(int n);

private:

  static constexpr int MAXTEXTURES = 32;  // 0 - 31

  int active_tex;

  int num_loaded_textures;

  unsigned int texture[MAXTEXTURES];

  int width, height, nrChannel;

  bool initiated;

};
