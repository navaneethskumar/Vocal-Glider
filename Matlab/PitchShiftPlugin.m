classdef PitchShiftPlugin < audioPlugin
    properties
        % Define plugin parameters here
        PitchShiftRatio = 1.0; % Initialize with no pitch shift
        % Add other parameters like gains, etc., as needed
    end

    methods
        function obj=PitchShiftPlugin()
            
        end
        function out = process(obj,inputSignal, pitchShiftRatio)
            % Parameters
            windowSize = 1024;
            hopSize = windowSize / 4;

            % STFT
            spect = stft(inputSignal, windowSize, hopSize);

            % Modify Phase for Pitch Shifting
            spectPhase = angle(spect);
            spectMag = abs(spect);
            spectPhaseShifted = spectPhase * pitchShiftRatio; % Apply pitch shift
            spectShifted = spectMag .* exp(1i * spectPhaseShifted);

            % ISTFT
            out = istft(spectShifted, windowSize, hopSize);
        end

        % STFT Function
        function spect = stft(signal, windowSize, hopSize)
            numFrames = floor((length(signal) - windowSize) / hopSize) + 1;
            spect = zeros(windowSize, numFrames);
            window = hann(windowSize, 'periodic');

            for i = 1:numFrames
                startIndex = (i - 1) * hopSize + 1;
                endIndex = startIndex + windowSize - 1;
                frame = signal(startIndex:endIndex);
                frame = frame .* window;
                spect(:, i) = fft(frame);
            end
        end

        % ISTFT Function
        function signal = istft(spect, windowSize, hopSize)
            numFrames = size(spect, 2);
            signalLength = (numFrames - 1) * hopSize + windowSize;
            signal = zeros(signalLength, 1);
            window = hann(windowSize, 'periodic');

            for i = 1:numFrames
                startIndex = (i - 1) * hopSize + 1;
                endIndex = startIndex + windowSize - 1;
                frame = ifft(spect(:, i));
                frame = real(frame) .* window;
                signal(startIndex:endIndex) = signal(startIndex:endIndex) + frame;
            end
        end
    end
end