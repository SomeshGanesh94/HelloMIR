x = [1.0, -0.2, 0.3, -0.6];
iBlockLength = 4;
iHopLength = iBlockLength;
f_s = 44100;
[vrms, t] = FeatureTimeRms(x, iBlockLength, iHopLength, f_s);

function [vrms, t] = FeatureTimeRms(x, iBlockLength, iHopLength, f_s)

    % number of results
    iNumOfBlocks    = ceil (length(x)/iHopLength);
    
    % compute time stamps
    t               = ((0:iNumOfBlocks-1) * iHopLength + (iBlockLength/2))/f_s;
    
    % allocate memory
    vrms            = zeros(1,iNumOfBlocks);

    for (n = 1:iNumOfBlocks)
        i_start     = (n-1)*iHopLength + 1;
        i_stop      = min(length(x),i_start + iBlockLength - 1);
        
        % calculate the rms
        vrms(n)     = sqrt(mean(x(i_start:i_stop).^2));
    end
 
    % convert to dB
    epsilon         = 1e-5; %-100dB
    
    vrms(vrms < epsilon)    = epsilon;
    vrms                    = 20*log10(vrms);
end