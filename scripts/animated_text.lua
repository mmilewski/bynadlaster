print('animatedtext.lua: [ LOADING ]');

local engine = Engine.Get();
local text_factory = engine:NonEntityFactory();


print('animatedtext.lua: [ CREATING AnimatedTextSinus ]');
class 'AnimatedTextSinus' (AnimatedText);

function AnimatedTextSinus:__init()
   AnimatedText.__init(self);
end

function AnimatedTextSinus:Draw()
   print('AnimatedTextSinus:Draw');
end

function AnimatedTextSinus:Update(dt)
   print('AnimatedTextSinus:Update(' .. dt .. ')');
end
print('animatedtext.lua: [ CREATING AnimatedTextSinus DONE ]');

print('animatedtext.lua: [ REGISTERING AnimatedTextSinus DONE ]');
local sinus_prototype = AnimatedTextSinus();
text_factory:RegisterAnimatedText("AnimatedTextSinus", sinus_prototype);
print('animatedtext.lua: [ REGISTERING AnimatedTextSinus DONE ]');



print('animatedtext.lua: [ LOADED ]');