classdef AmplitudeModulation < audioPlugin
    properties
        phase
        modulationFrequency = 20
        modulationDepth = 0.5
        sampleRate
        buffLength=512
    end
    properties(Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('modulationDepth', ...
                'DisplayName', 'Depth', ...
                'Label', 's', ...
                'Mapping', { 'lin', -2*pi, 2*pi }), ... % Adjust the range as needed
            audioPluginParameter('modulationFrequency', ...
                'DisplayName', 'Rate', ...
                'Label', 'Hz', ...
                'Mapping', { 'log', 20,2000}));
    end
    methods
        function obj = AmplitudeModulation()
            obj.buffLength= 512;
            obj.phase = 0.0;
            obj.modulationFrequency = 500.0;
            obj.modulationDepth = 0.5;
            obj.sampleRate = 44100.0;
        end
        
        function obj = prepareToPlay(obj, newSampleRate)
            obj.sampleRate = newSampleRate;
        end
        
        function [buffer,obj] = process(obj, buffer)
            numChannels = size(buffer, 2);
%             obj.modulationDepth = ;
%             obj.modulationFrequency = frequency;
            
            for channel = 1:numChannels
                channelData = buffer(:, channel);
                
                phaseIncrement = obj.modulationFrequency / obj.sampleRate;
                
                for sample = 1:size(buffer, 1)
                    modulatedSample = channelData(sample) * sin(obj.phase);
                    channelData(sample) = channelData(sample) + obj.modulationDepth * modulatedSample;
                    
                    obj.phase = obj.phase + phaseIncrement;

                
                    if obj.phase >= 2 * pi
                        obj.phase = obj.phase - 2 * pi;
                    end
                end
                
                buffer(:, channel) = channelData;
            end
        end
    end
end

% % Example usage:
% sampleRate = 44100;
% duration = 5; % in seconds
% t = (0:1/sampleRate:duration-1/sampleRate).';
% signal = sin(2 * pi * 440 * t); % Example input signal (440 Hz sine wave)
% buffer = [signal, signal]; % Stereo signal
% 
% modulator = PhaseModulation();
% modulator.prepareToPlay(sampleRate);
% 
% % Apply phase modulation with a frequency of 500 Hz and depth of 0.5
% modulator.processBlock(buffer, 500, 0.5);
% 
% % At this point, 'buffer' contains the phase-modulated audio signal
