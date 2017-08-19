
```cpp
auto tweenManager = std::make_shared<NTweenManager>();
this->add(tweenManager);

tweenManager->tween(
    std::make_shared<NColorTween>(this->_clearColor, NColor::fromRGBInt(100, 100, 100),
    EaseFunctions::EASE_LINEAR), 1.0f);
```
