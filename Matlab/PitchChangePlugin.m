classdef PitchChangePlugin < audioPlugin
    properties
        PitchShiftRatio = 1.4; % Set the default pitch-shifting ratio
    end
    
    methods
        function obj=PitchChangePlugin
        end    
        function out = process(obj, in)
            % Parameters
            s_win = 2048;   % Analysis window length [samples]
            n1 = 512;       % Synthesis window length [samples]
            
            % Initialize windows, arrays, etc
            w1 = hanning(s_win, 'periodic'); % Analysis window
            w2 = w1;                         % Synthesis window

            % Preallocate output buffer
            DAFx_out = zeros(length(in) + s_win, 1);

            grain = zeros(s_win, 1);
            hs_win = s_win / 2;
            omega = 2 * pi * n1 * (0:hs_win - 1)' / s_win;
            phi0 = zeros(hs_win, 1);
            r0 = zeros(hs_win, 1);
            psi = phi0;
            res = zeros(n1, 1);

            pin = 0;
            pout = 0;
            pend = length(in) - s_win;

            while pin < pend
                grain = in(pin + 1:pin + s_win) .* w1;

                % Fourier transform
                fc = fft(fftshift(grain));
                f = fc(1:hs_win);
                r = abs(f);
                phi = angle(f);

                % Compute phase & magnitude increments
                delta_phi = omega + princarg(phi - phi0 - omega);
                delta_r = (r - r0) / n1;
                delta_psi = obj.PitchShiftRatio * delta_phi / n1;

                % Compute output buffer
                for k = 1:n1
                    r0 = r0 + delta_r;
                    psi = psi + delta_psi;
                    res(k) = r0' * cos(psi);
                end

                % Store for the next block
                phi0 = phi;
                r0 = r;
                psi = princarg(psi);

                DAFx_out(pout + 1:pout + n1) = DAFx_out(pout + 1:pout + n1) + res;
                pin = pin + n1;
                pout = pout + n1;
            end

            % Output the processed audio
            out = DAFx_out(hs_win + n1 + 1:hs_win + n1 + length(in)) / max(abs(DAFx_out));
        end
    end
end

% Function to wrap angles to the principal argument range
function result = princarg(phi)
    result = mod(phi + pi, 2 * pi) - pi;
end
