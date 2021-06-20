# Top Audio Filters

A music effect

This a music audio effects implementation based on LabSound(split from Webkit).

# Examples

```c++
    // make a audio context
    auto context = makeOfflineAudioContext();
    // created a audio processor
    AudioProcessor processor(std::move(context));

    
    // created  a 4-bands EQ effect
    std::vector<float> freqs = std::vector<float>(4);
    freqs[0] = 320;
    freqs[1] = 1000;
    freqs[2] = 3200;
    freqs[3] = 6400;
    EffectEQProcessor effectEqProcessor(*processor.ac,freqs);
    effectEqProcessor.updateGain(std::vector<float>{
    0.0,
    0.0,
    0.0,
    0.0});

    // generate  samples from file
    // in real case, you can directly construct the AudioBus as Input.
    std::shared_ptr<lab::AudioBus> musicClip = lab::MakeBusFromFile("samples/stereo-music-clip.wav", true);

    // connect the effect to audio processor
    effectEqProcessor.setInput(processor.inputNode);
    effectEqProcessor.setOutput(processor.outputNode);
    
    //the output already render as effects
    auto output = processor.process(musicClip);
    

```

# List Audio Effects

## N Bands EQ

```
params:
    - frequencies. N bands frequencies and needs sort by frequency. 
        the first frequency as LowShelf, last as HighShelf, others as Peaking.
    - gains
        -24 - +24, defaults as 0.
```
## Reverb

```
params:
    - reverb time.
    - decay.
    - mix.  defined how to mix wet sound & dry sound. 
```
## Delay
//todo:

## Distortion
//todo:

## Compressor
//todo:

## Limiter
//todo:

## Quadrafuzz
//todo:




