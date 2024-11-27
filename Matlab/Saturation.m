classdef Saturation < audioPlugin
    %DISTORTION Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        drive=200
        bias=20
    end
    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('drive', ...
                'DisplayName', 'drive', ...
                'Label', 'db', ...
                'Mapping', { 'lin', 0.1, 20 }),...
                audioPluginParameter('bias', ...
                'DisplayName', 'bias', ...
                'Label', 'db', ...
                'Mapping', { 'lin', 0.0, 1.0 }));
    end
    
    methods
        function obj = Saturation()
            %DISTORTION Construct an instance of this class
            %   Detailed explanation goes here
            obj.drive = 1.0;
        end
        function obj = setDistortion(obj,distortion)
            obj.drive=distortion;
        end    
        
        function output = process(obj,input)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            output=zeros(size(input,1),1);
            for n=1:size(input,1)
        
                saturation = 2 * atan(obj.drive * input) / pi;
                output = (1 + obj.bias) * (input - obj.bias * saturation);
            
            end
        end
    end
end

