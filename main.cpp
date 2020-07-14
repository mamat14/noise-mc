#include "AudioFile.h"
#include <iostream>
#include <math.h>

double MAIN_PARAM = 0;

void applyFilter(std::vector<double> source, std::vector<double>& dest, int numSamples, int sample_rate) {
  double W = 1.0 / tan(M_PI * (MAIN_PARAM / sample_rate));
  double q = sqrt(2);
  double B0 = 1 / (1 + q*W + W*W);
  double B1 = 2 * B0;
  double B2 = B0;
  double A1 = 2*B0*(W*W - 1.0);
  double A2 = -(1 - q*W + W*W) * B0;

  std::cout << B0 << " " << B1 << " " << B2 << " " << A1 << " " << A2 << std::endl;
  dest[0] = 0;
  dest[1] = 0;
  for (int i = 2; i < numSamples; i++) {
    dest[i] = B0*source[i] + B1 * source[i-1] + B2 * source[i-2] + A1 * dest[i-1] + A2 * dest[i-2];
  }
}

int main() {
  std::cin >> MAIN_PARAM;
  AudioFile<double> audioFile;
  audioFile.load ("./file.wav");
  int numChannels = audioFile.getNumChannels();
  auto sampleRate = audioFile.getSampleRate();
  std::cout << "Sample rate: " << sampleRate << std::endl;
  AudioFile<double>::AudioBuffer buffer;
  buffer.resize (numChannels);
  for (int i = 0; i < numChannels; i++) {
    int numSamples = audioFile.getNumSamplesPerChannel();
    buffer[i].resize(numSamples);
  }

  for (int i = 0; i < numChannels; i++){
    int numSamples = audioFile.getNumSamplesPerChannel();
    auto source = audioFile.samples[i];
    applyFilter(source, buffer[i], numSamples, sampleRate);

    for(int j = 0; j < 100; ++j) {
      std::cout << buffer[i][j] << ", ";
    }
  }
  audioFile.setAudioBuffer (buffer);
  audioFile.save("./file_copy.wav");
  return 0;
}
